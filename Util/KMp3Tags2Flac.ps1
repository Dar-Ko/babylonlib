#!/usr/bin/env pwsh
<#
.SYNOPSIS
    Copies ALL metadata (including album art) from MP3 files to matching FLAC files
.DESCRIPTION
    Matches .flac files in source directory with .mp3 files in reference directory
    by filename (without extension) and copies ALL metadata from MP3 to FLAC
.PARAMETER FlacDir
    Directory containing FLAC files to update
.PARAMETER Mp3Dir
    Directory containing MP3 files with source metadata
.PARAMETER DryRun
    If specified, shows what would be done without making changes
.PARAMETER Backup
    If specified, creates backup of FLAC files before modification
.EXAMPLE
    ./Copy-Metadata.ps1 -FlacDir "/music/flac" -Mp3Dir "/music/mp3"
.EXAMPLE
    ./Copy-Metadata.ps1 -FlacDir "C:\Music\FLAC" -Mp3Dir "C:\Music\MP3" -DryRun
.EXAMPLE
    ./Copy-Metadata.ps1 -FlacDir "/music/flac" -Mp3Dir "/music/mp3" -Backup
.NOTES
    Date:    2026-06-01
    Version: %VERSION-HASH%
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory=$true)]
    [string]$FlacDir,
    
    [Parameter(Mandatory=$true)]
    [string]$Mp3Dir,
    
    [switch]$DryRun,
    
    [switch]$Backup
)

# Check if running on Windows or Linux
$isWindows = $env:OS -eq 'Windows_NT'

# Function to check if required tools are installed
function Test-RequiredTools {
    $missingTools = @()
    
    # Check for ffmpeg
    $ffmpeg = Get-Command ffmpeg -ErrorAction SilentlyContinue
    if (-not $ffmpeg) {
        $missingTools += "ffmpeg"
    }
    
    # Check for metaflac
    $metaflac = Get-Command metaflac -ErrorAction SilentlyContinue
    if (-not $metaflac) {
        $missingTools += "metaflac"
    }
    
    if ($missingTools.Count -gt 0) {
        Write-Warning "Missing required tools: $($missingTools -join ', ')"
        Write-Warning "Install with:"
        if ($isWindows) {
            Write-Warning "  choco install ffmpeg flac"
            Write-Warning "  OR download from:"
            Write-Warning "    ffmpeg: https://ffmpeg.org/download.html"
            Write-Warning "    flac: https://xiph.org/flac/download.html"
        } else {
            Write-Warning "  sudo apt update"
            Write-Warning "  sudo apt install ffmpeg flac"
        }
        return $false
    }
    
    return $true
}

# Function to extract ALL metadata from MP3 file including album art
function Get-MP3AllMetadata {
    param([string]$Mp3Path)
    
    if (-not (Test-Path $Mp3Path)) {
        Write-Warning "MP3 file not found: $Mp3Path"
        return $null
    }
    
    Write-Verbose "Extracting metadata from: $Mp3Path"
    
    # Create temporary directory for extracted data
    $tempDir = Join-Path $env:TEMP "mp3_metadata_$(Get-Random)"
    New-Item -ItemType Directory -Path $tempDir -Force | Out-Null
    
    try {
        # Extract all metadata including cover art using ffmpeg
        $outputFile = Join-Path $tempDir "metadata.txt"
        
        # Run ffmpeg to get all metadata
        & ffmpeg -i $Mp3Path -f ffmetadata $outputFile 2>&1 | Out-Null
        
        # Read the metadata
        $metadata = @{}
        $coverArtExtracted = $false
        
        if (Test-Path $outputFile) {
            $content = Get-Content $outputFile -Raw
            $lines = $content -split "`r?`n"
            
            foreach ($line in $lines) {
                if ($line -match '^([^=]+)=(.*)$') {
                    $key = $matches[1].Trim()
                    $value = $matches[2].Trim()
                    $metadata[$key] = $value
                }
            }
        }
        
        # Extract album art using ffmpeg
        $coverFile = Join-Path $tempDir "cover.jpg"
        & ffmpeg -i $Mp3Path -an -vcodec copy $coverFile 2>&1 | Out-Null
        
        if (Test-Path $coverFile) {
            $coverArt = [System.IO.File]::ReadAllBytes($coverFile)
            $metadata['COVER_ART'] = $coverArt
            $metadata['COVER_ART_FILENAME'] = "cover.jpg"
            Write-Verbose "  ✓ Extracted album art ($($coverArt.Length) bytes)"
        } else {
            Write-Verbose "  No album art found"
        }
        
        # Also use ffprobe to get additional metadata that ffmpeg might miss
        $ffprobeOutput = & ffprobe -v quiet -print_format json -show_format -show_streams $Mp3Path | ConvertFrom-Json
        
        if ($ffprobeOutput.format.tags) {
            $tags = $ffprobeOutput.format.tags.PSObject.Properties
            foreach ($tag in $tags) {
                $key = $tag.Name
                $value = $tag.Value
                if (-not $metadata.ContainsKey($key)) {
                    $metadata[$key] = $value
                }
            }
        }
        
        Write-Verbose "  Extracted $($metadata.Count) metadata fields (including possible cover art)"
        return $metadata
    }
    catch {
        Write-Warning "Error extracting metadata from $Mp3Path : $_"
        return $null
    }
    finally {
        # Clean up temp directory
        Remove-Item -Path $tempDir -Recurse -Force -ErrorAction SilentlyContinue
    }
}

# Function to convert Windows paths for metaflac on Windows
function Convert-PathForMetaflac {
    param([string]$Path)
    
    if ($isWindows) {
        # Convert backslashes to forward slashes for metaflac on Windows
        return $Path.Replace('\', '/')
    }
    return $Path
}

# Function to copy ALL metadata to FLAC file
function Set-FLACAllMetadata {
    param(
        [string]$FlacPath,
        [hashtable]$Metadata
    )
    
    if (-not (Test-Path $FlacPath)) {
        Write-Warning "FLAC file not found: $FlacPath"
        return $false
    }
    
    if ($Metadata.Count -eq 0) {
        Write-Warning "No metadata to copy for: $FlacPath"
        return $false
    }
    
    # Create backup if requested
    if ($Backup -and -not $DryRun) {
        $backupPath = "$FlacPath.backup"
        Copy-Item -Path $FlacPath -Destination $backupPath -Force
        Write-Verbose "  Backup created: $backupPath"
    }
    
    if ($DryRun) {
        Write-Host "[DRY RUN] Would update: $FlacPath" -ForegroundColor Cyan
        Write-Host "  Metadata fields to apply:" -ForegroundColor Gray
        foreach ($key in $Metadata.Keys) {
            if ($key -eq 'COVER_ART') {
                Write-Host "    $key : [Binary data - $($Metadata[$key].Length) bytes]" -ForegroundColor Gray
            } elseif ($key -ne 'COVER_ART_FILENAME') {
                $value = $Metadata[$key]
                if ($value.Length -gt 50) { $value = $value.Substring(0, 47) + "..." }
                Write-Host "    $key : $value" -ForegroundColor Gray
            }
        }
        return $true
    }
    
    try {
        # First, remove all existing tags from FLAC (optional - comment out if you want to merge)
        $removeCmd = @("--remove-all-tags", "`"$FlacPath`"")
        & metaflac $removeCmd 2>&1 | Out-Null
        
        # Build metaflac commands for each metadata field
        $metaflacArgs = @()
        
        foreach ($key in $Metadata.Keys) {
            # Skip internal keys
            if ($key -eq 'COVER_ART_FILENAME') { continue }
            
            # Handle album art specially
            if ($key -eq 'COVER_ART') {
                $tempCoverFile = [System.IO.Path]::GetTempFileName() + ".jpg"
                try {
                    [System.IO.File]::WriteAllBytes($tempCoverFile, $Metadata[$key])
                    
                    # Import cover art to FLAC
                    $importCmd = @(
                        "--import-picture-from=`"$tempCoverFile`"",
                        "`"$FlacPath`""
                    )
                    & metaflac $importCmd 2>&1 | Out-Null
                    
                    if ($LASTEXITCODE -eq 0) {
                        Write-Verbose "  ✓ Added album art"
                    } else {
                        Write-Warning "  Failed to add album art"
                    }
                }
                finally {
                    if (Test-Path $tempCoverFile) {
                        Remove-Item $tempCoverFile -Force -ErrorAction SilentlyContinue
                    }
                }
                continue
            }
            
            # Convert key to Vorbis comment format (uppercase)
            $tagName = $key.ToUpper()
            
            # Handle special tag name mappings
            switch ($key.ToLower()) {
                'track' { $tagName = 'TRACKNUMBER' }
                'tracknumber' { $tagName = 'TRACKNUMBER' }
                'disc' { $tagName = 'DISCNUMBER' }
                'discnumber' { $tagName = 'DISCNUMBER' }
                'comment' { $tagName = 'DESCRIPTION' }
                'date' { $tagName = 'DATE' }
                'year' { $tagName = 'DATE' }
                'lyrics' { $tagName = 'LYRICS' }
                'composer' { $tagName = 'COMPOSER' }
                'performer' { $tagName = 'PERFORMER' }
                'copyright' { $tagName = 'COPYRIGHT' }
                'organization' { $tagName = 'ORGANIZATION' }
            }
            
            $value = $Metadata[$key]
            
            # Skip empty values
            if ([string]::IsNullOrWhiteSpace($value)) { continue }
            
            # Escape special characters in value
            $value = $value -replace '"', '\"'
            
            # Add tag to metaflac arguments
            $metaflacArgs += "--set-tag=`"$tagName=$value`""
        }
        
        # Add the FLAC file path
        $flacPathConverted = Convert-PathForMetaflac -Path $FlacPath
        $metaflacArgs += "`"$flacPathConverted`""
        
        # Execute metaflac if we have tags to add
        if ($metaflacArgs.Count -gt 1) {
            & metaflac $metaflacArgs
            
            if ($LASTEXITCODE -eq 0) {
                Write-Host "✓ Updated: $(Split-Path $FlacPath -Leaf)" -ForegroundColor Green
                return $true
            } else {
                Write-Warning "Failed to update: $(Split-Path $FlacPath -Leaf) (exit code: $LASTEXITCODE)"
                return $false
            }
        } else {
            Write-Host "○ No tags to add: $(Split-Path $FlacPath -Leaf)" -ForegroundColor Yellow
            return $true
        }
    }
    catch {
        Write-Warning "Error updating $FlacPath : $_"
        return $false
    }
}

# Function to verify FLAC metadata after update
function Test-FLACMetadata {
    param([string]$FlacPath)
    
    $output = & metaflac --list "$FlacPath" 2>&1 | Out-String
    
    $tagCount = ($output | Select-String -Pattern "^comment" -AllMatches).Matches.Count
    $hasPicture = ($output | Select-String -Pattern "METADATA block #.*type: 6 \(PICTURE\)" -AllMatches).Matches.Count -gt 0
    
    return @{
        TagCount = $tagCount
        HasPicture = $hasPicture
    }
}

# Main execution
function Main {
    Write-Host "MP3 to FLAC - Complete Metadata Copier" -ForegroundColor Magenta
    Write-Host "=======================================" -ForegroundColor Magenta
    Write-Host "FLAC Directory: $FlacDir"
    Write-Host "MP3 Directory: $Mp3Dir"
    if ($DryRun) { Write-Host "Mode: DRY RUN (no changes will be made)" -ForegroundColor Yellow }
    if ($Backup) { Write-Host "Backup: Enabled (backup files will be created with .backup extension)" -ForegroundColor Cyan }
    Write-Host ""
    
    # Check if directories exist
    if (-not (Test-Path $FlacDir)) {
        Write-Error "FLAC directory not found: $FlacDir"
        return 1
    }
    
    if (-not (Test-Path $Mp3Dir)) {
        Write-Error "MP3 directory not found: $Mp3Dir"
        return 1
    }
    
    # Check required tools
    if (-not (Test-RequiredTools)) {
        return 1
    }
    
    # Get all FLAC files
    $flacFiles = Get-ChildItem -Path $FlacDir -Filter "*.flac" -File
    Write-Host "Found $($flacFiles.Count) FLAC files" -ForegroundColor Cyan
    
    $successCount = 0
    $skipCount = 0
    $failCount = 0
    $filesWithArt = 0
    
    foreach ($flacFile in $flacFiles) {
        $baseName = [System.IO.Path]::GetFileNameWithoutExtension($flacFile.Name)
        $mp3File = Join-Path $Mp3Dir "$baseName.mp3"
        
        Write-Verbose "Matching FLAC: $baseName with MP3: $(Split-Path $mp3File -Leaf)"
        
        if (Test-Path $mp3File) {
            Write-Host "Processing: $baseName" -ForegroundColor Yellow
            
            # Extract ALL metadata from MP3
            $metadata = Get-MP3AllMetadata -Mp3Path $mp3File
            
            if ($metadata -and $metadata.Count -gt 0) {
                $hasArt = $metadata.ContainsKey('COVER_ART')
                
                # Copy metadata to FLAC
                if (Set-FLACAllMetadata -FlacPath $flacFile.FullName -Metadata $metadata) {
                    $successCount++
                    if ($hasArt) { $filesWithArt++ }
                    
                    # Verify the update (only in verbose mode)
                    if ($VerbosePreference -eq 'Continue') {
                        $verification = Test-FLACMetadata -FlacPath $flacFile.FullName
                        Write-Verbose "  Verification: $($verification.TagCount) tags, Has picture: $($verification.HasPicture)"
                    }
                } else {
                    $failCount++
                }
            } else {
                Write-Warning "No metadata found in MP3: $mp3File"
                $skipCount++
            }
        } else {
            Write-Verbose "No matching MP3 found for: $baseName"
            $skipCount++
        }
    }
    
    # Summary
    Write-Host ""
    Write-Host "Summary:" -ForegroundColor Magenta
    Write-Host "  Successful updates: $successCount" -ForegroundColor Green
    Write-Host "    - Includes album art: $filesWithArt" -ForegroundColor Green
    Write-Host "  Skipped (no match/no metadata): $skipCount" -ForegroundColor Yellow
    Write-Host "  Failed: $failCount" -ForegroundColor Red
    
    if ($successCount -gt 0) {
        Write-Host ""
        Write-Host "✓ All metadata including album art has been copied" -ForegroundColor Green
    }
    
    if ($DryRun -and $successCount -gt 0) {
        Write-Host ""
        Write-Host "This was a DRY RUN. Run without -DryRun to apply changes." -ForegroundColor Yellow
    }
    
    if ($Backup -and -not $DryRun -and $successCount -gt 0) {
        Write-Host ""
        Write-Host "Backup files created with .backup extension. To restore:" -ForegroundColor Cyan
        Write-Host "  Get-ChildItem *.backup | ForEach-Object { Copy-Item `$_.FullName `$_.FullName.Replace('.backup','') }" -ForegroundColor Gray
    }
    
    return 0
}

# Run the script
exit (Main)