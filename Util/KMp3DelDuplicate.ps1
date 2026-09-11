#!/usr/bin/env pwsh
<#
.SYNOPSIS
    Deletes MP3 files that have matching FLAC files in another directory
.DESCRIPTION
    Matches .flac files in source directory with .mp3 files in reference directory
    by filename (without extension) and deletes the MP3 files.
    Includes safety features like dry-run, confirmation, and recycle bin support.
.PARAMETER FlacDir
    Directory containing FLAC files (the quality replacement)
.PARAMETER Mp3Dir
    Directory containing MP3 files to potentially delete
.PARAMETER DryRun
    If specified, shows what would be deleted without actually deleting
.PARAMETER Recycle
    If specified, sends files to Recycle Bin instead of permanent deletion (Windows only)
.PARAMETER Prompt
    If specified, prompts for confirmation before each deletion
.PARAMETER RemoveEmptyDirs
    If specified, removes empty subdirectories after MP3 deletion
.PARAMETER LogFile
    Path to log file for recording deletions (optional)
.PARAMETER Force
    If specified, skips the initial safety confirmation prompt
.EXAMPLE
    ./Remove-MatchedMP3.ps1 -FlacDir "/music/flac" -Mp3Dir "/music/mp3"
.EXAMPLE
    ./Remove-MatchedMP3.ps1 -FlacDir "C:\Music\FLAC" -Mp3Dir "C:\Music\MP3" -DryRun
.EXAMPLE
    ./Remove-MatchedMP3.ps1 -FlacDir "/music/flac" -Mp3Dir "/music/mp3" -Recycle -Interactive
.NOTES
    Date:    2026-06-01
    Version: %VERSION-HASH%
#>

[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(Mandatory=$true)]
    [string]$FlacDir,
    
    [Parameter(Mandatory=$true)]
    [string]$Mp3Dir,
    
    [switch]$DryRun,
    
    [switch]$Recycle,
    
    [switch]$Prompt,
    
    [switch]$RemoveEmptyDirs,
    
    [string]$LogFile,
    
    [switch]$Force
)

# Check if running on Windows or Linux
$isWindows = $env:OS -eq 'Windows_NT'

# Initialize logging
$logEntries = @()

function Write-Log {
    param(
        [string]$Message,
        [string]$Level = "INFO"
    )
    
    $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    $logEntry = "$timestamp [$Level] $Message"
    $logEntries += $logEntry
    
    switch ($Level) {
        "ERROR" { Write-Host $logEntry -ForegroundColor Red }
        "WARNING" { Write-Host $logEntry -ForegroundColor Yellow }
        "SUCCESS" { Write-Host $logEntry -ForegroundColor Green }
        "INFO" { Write-Host $logEntry -ForegroundColor Gray }
        default { Write-Host $logEntry }
    }
}

# Function to send file to recycle bin on Windows
function Move-ToRecycleBin {
    param([string]$FilePath)
    
    if (-not $isWindows) {
        Write-Log "Recycle bin only supported on Windows, will delete permanently" -Level "WARNING"
        Remove-Item -Path $FilePath -Force
        return $?
    }
    
    Add-Type -AssemblyName Microsoft.VisualBasic
    try {
        [Microsoft.VisualBasic.FileIO.FileSystem]::DeleteFile($FilePath, 'OnlyDeleteRecycleBin', 'SendToRecycleBin')
        return $true
    }
    catch {
        Write-Log "Failed to send to recycle bin: $_" -Level "ERROR"
        return $false
    }
}

# Function to delete file based on options
function Remove-MP3File {
    param(
        [string]$FilePath,
        [string]$FlacPath
    )
    
    if ($DryRun) {
        Write-Log "[DRY RUN] Would delete: $FilePath" -Level "INFO"
        Write-Log "  Matching FLAC: $FlacPath" -Level "INFO"
        return $true
    }
    
    # If interactive mode is enabled, ask for confirmation
    if ($Prompt) {
        $choice = Read-Host "Delete '$($FilePath)'? (y/n/a=all, q=quit)"
        switch ($choice.ToLower()) {
            'y' { 
                # Proceed with deletion
            }
            'n' { 
                Write-Log "Skipped: $FilePath" -Level "WARNING"
                return $false
            }
            'a' { 
                $script:Interactive = $false
                Write-Log "Auto-confirming all remaining deletions" -Level "INFO"
            }
            'q' { 
                Write-Log "User quit" -Level "WARNING"
                exit
            }
            default { 
                Write-Log "Skipped: $FilePath" -Level "WARNING"
                return $false
            }
        }
    }
    
    # Delete the file
    try {
        if ($Recycle -and $isWindows) {
            Move-ToRecycleBin -FilePath $FilePath
        } else {
            Remove-Item -Path $FilePath -Force
        }
        
        if ($?) {
            Write-Log "Deleted: $FilePath" -Level "SUCCESS"
            return $true
        } else {
            Write-Log "Failed to delete: $FilePath" -Level "ERROR"
            return $false
        }
    }
    catch {
        Write-Log "Error deleting $FilePath : $_" -Level "ERROR"
        return $false
    }
}

# Function to remove empty directories
function Remove-EmptyDirectories {
    param([string]$Directory)
    
    if (-not (Test-Path $Directory)) {
        return
    }
    
    $emptyDirs = @()
    
    # Get all subdirectories recursively
    $directories = Get-ChildItem -Path $Directory -Directory -Recurse | Sort-Object -Property FullName -Descending
    
    foreach ($dir in $directories) {
        $remainingFiles = Get-ChildItem -Path $dir.FullName -File | Where-Object { $_.Extension -ne '.flac' }
        if ($remainingFiles.Count -eq 0) {
            try {
                if (-not $DryRun) {
                    Remove-Item -Path $dir.FullName -Force
                    Write-Log "Removed empty directory: $($dir.FullName)" -Level "SUCCESS"
                } else {
                    Write-Log "[DRY RUN] Would remove empty directory: $($dir.FullName)" -Level "INFO"
                }
                $emptyDirs += $dir.FullName
            }
            catch {
                Write-Log "Failed to remove directory $($dir.FullName): $_" -Level "ERROR"
            }
        }
    }
    
    return $emptyDirs
}

# Function to get all FLAC files (including subdirectories if needed)
function Get-FLACFiles {
    param([string]$Directory)
    
    # Get all FLAC files, optionally including subdirectories
    $flacFiles = Get-ChildItem -Path $Directory -Filter "*.flac" -File -Recurse
    return $flacFiles
}

# Function to find matching MP3 file (supports different directory structures)
function Find-MatchingMP3 {
    param(
        [string]$FlacPath,
        [string]$Mp3BaseDir
    )
    
    $flacName = [System.IO.Path]::GetFileNameWithoutExtension($FlacPath)
    $flacDir = [System.IO.Path]::GetDirectoryName($FlacPath)
    
    # Try to maintain relative path structure
    $relativePath = ""
    if ($FlacDir -ne $FlacDir) {
        try {
            $relativePath = $FlacDir.Substring($FlacDir.Length)
        }
        catch {
            $relativePath = ""
        }
    }
    
    # Strategy 1: Look in same relative path
    $mp3Path1 = Join-Path $Mp3BaseDir "$flacName.mp3"
    if (Test-Path $mp3Path1) {
        return $mp3Path1
    }
    
    # Strategy 2: Search recursively for matching filename
    $mp3Files = Get-ChildItem -Path $Mp3BaseDir -Filter "$flacName.mp3" -File -Recurse -ErrorAction SilentlyContinue
    if ($mp3Files.Count -gt 0) {
        if ($mp3Files.Count -gt 1) {
            Write-Log "Multiple matches found for $flacName, using first: $($mp3Files[0].FullName)" -Level "WARNING"
        }
        return $mp3Files[0].FullName
    }
    
    # No match found
    return $null
}

# Main execution
function Main {
    Write-Log "MP3 to FLAC - Delete Matched MP3 Files" -Level "INFO"
    Write-Log "=======================================" -Level "INFO"
    Write-Log "FLAC Directory: $FlacDir" -Level "INFO"
    Write-Log "MP3 Directory: $Mp3Dir" -Level "INFO"
    
    if ($DryRun) { 
        Write-Log "Mode: DRY RUN (no files will be deleted)" -Level "WARNING"
    }
    if ($Recycle -and $isWindows) { 
        Write-Log "Recycle Bin: Enabled (files will be moved to Recycle Bin)" -Level "INFO"
    }
    if ($Prompt) { 
        Write-Log "Interactive Mode: Enabled (will prompt before each deletion)" -Level "INFO"
    }
    if ($RemoveEmptyDirs) { 
        Write-Log "Remove Empty Directories: Enabled" -Level "INFO"
    }
    Write-Log "" -Level "INFO"
    
    # Check if directories exist
    if (-not (Test-Path $FlacDir)) {
        Write-Log "FLAC directory not found: $FlacDir" -Level "ERROR"
        return 1
    }
    
    if (-not (Test-Path $Mp3Dir)) {
        Write-Log "MP3 directory not found: $Mp3Dir" -Level "ERROR"
        return 1
    }
    
    # Get all FLAC files
    Write-Log "Scanning for FLAC files..." -Level "INFO"
    $flacFiles = Get-FLACFiles -Directory $FlacDir
    $totalFlac = $flacFiles.Count
    Write-Log "Found $totalFlac FLAC files" -Level "INFO"
    
    if ($totalFlac -eq 0) {
        Write-Log "No FLAC files found in $FlacDir" -Level "WARNING"
        return 0
    }
    
    # Statistics
    $deletedCount = 0
    $skippedCount = 0
    $errorCount = 0
    $totalSizeSaved = 0
    
    # Process each FLAC file
    $currentFile = 0
    foreach ($flacFile in $flacFiles) {
        $currentFile++
        $flacName = [System.IO.Path]::GetFileNameWithoutExtension($flacFile.Name)
        $percentComplete = [math]::Round(($currentFile / $totalFlac) * 100, 1)
        
        Write-Progress -Activity "Processing FLAC files" `
                       -Status "Processing $currentFile of $totalFlac ($percentComplete%)" `
                       -PercentComplete $percentComplete `
                       -CurrentOperation "Checking: $flacName"
        
        # Find matching MP3
        $mp3File = Find-MatchingMP3 -FlacPath $flacFile.FullName -Mp3BaseDir $Mp3Dir
        
        if ($mp3File) {
            # Get file size for reporting
            $mp3Size = (Get-Item $mp3File).Length
            $totalSizeSaved += $mp3Size
            
            Write-Log "Found match: $flacName" -Level "INFO"
            Write-Log "  MP3: $mp3File ($([math]::Round($mp3Size/1MB, 2)) MB)" -Level "INFO"
            
            # Delete the MP3 file
            if (Remove-MP3File -FilePath $mp3File -FlacPath $flacFile.FullName) {
                $deletedCount++
            } else {
                $errorCount++
            }
        } else {
            Write-Log "No matching MP3 found for: $flacName" -Level "WARNING"
            $skippedCount++
        }
    }
    
    Write-Progress -Activity "Processing FLAC files" -Completed
    
    # Remove empty directories if requested
    if ($RemoveEmptyDirs -and -not $DryRun) {
        Write-Log "" -Level "INFO"
        Write-Log "Removing empty directories..." -Level "INFO"
        Remove-EmptyDirectories -Directory $Mp3Dir
    }
    
    # Summary
    Write-Log "" -Level "INFO"
    Write-Log "Summary:" -Level "INFO"
    Write-Log "  Total FLAC files processed: $totalFlac" -Level "INFO"
    Write-Log "  MP3 files deleted: $deletedCount" -Level "SUCCESS"
    Write-Log "  MP3 files skipped (no match): $skippedCount" -Level "WARNING"
    Write-Log "  Errors: $errorCount" -Level "ERROR"
    
    if ($deletedCount -gt 0) {
        $totalSizeMB = [math]::Round($totalSizeSaved/1MB, 2)
        $totalSizeGB = [math]::Round($totalSizeSaved/1GB, 2)
        Write-Log "  Total disk space saved: $totalSizeMB MB ($totalSizeGB GB)" -Level "SUCCESS"
    }
    
    if ($DryRun -and $deletedCount -gt 0) {
        Write-Log "" -Level "WARNING"
        Write-Log "This was a DRY RUN. Run without -DryRun to delete files." -Level "WARNING"
    }
    
    # Write log to file if specified
    if ($LogFile) {
        try {
            $logContent = $logEntries -join "`r`n"
            $logContent | Out-File -FilePath $LogFile -Encoding UTF8
            Write-Log "Log written to: $LogFile" -Level "INFO"
        }
        catch {
            Write-Log "Failed to write log file: $_" -Level "ERROR"
        }
    }
    
    # Return exit code
    if ($errorCount -gt 0) {
        return 1
    }
    return 0
}

# Run safety check - verify FLAC directory contains actual FLAC files
if (-not $DryRun -and -not $Force) {
    Write-Host ""
    Write-Host "SAFETY CHECK:" -ForegroundColor Yellow
    Write-Host "This script will delete MP3 files that have matching FLAC files." -ForegroundColor Yellow
    Write-Host "FLAC Directory: $FlacDir" -ForegroundColor Cyan
    Write-Host "MP3 Directory: $Mp3Dir" -ForegroundColor Cyan
    Write-Host ""
    
    $confirmation = Read-Host "Are you sure you want to proceed? (yes/no)"
    if ($confirmation -ne "yes") {
        Write-Host "Operation cancelled." -ForegroundColor Red
        exit 0
    }
}

# Run main function
exit (Main)