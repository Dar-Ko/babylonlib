#!/usr/bin/env pwsh
<#
.SYNOPSIS
Searches for files by base name (ignoring extensions) from a source directory within a target directory tree,
and exports the results as a TSV file inside the source directory.

.DESCRIPTION
This script scans a source directory for all files, extracts their base names (without extensions),
then recursively searches a target directory for any files whose base name matches, regardless of extension.
The full path of each matching file is saved in a tab‑separated values (TSV) file inside the source directory.
The results are also displayed on the console.

.PARAMETER SourceDir
Path to the source directory containing the reference files (extensions are ignored).

.PARAMETER TargetDir
Path to the target directory where the search will be performed recursively.

.PARAMETER OutputFile
Optional name of the TSV output file. Default is "matched_files.tsv". The file is created inside $SourceDir.

.EXAMPLE
.\Find-FilesByBaseName.ps1 -SourceDir "C:\MyFiles" -TargetDir "D:\Backup"
Searches and saves results to C:\MyFiles\matched_files.tsv

.EXAMPLE
./Find-FilesByBaseName.ps1 -SourceDir "/home/user/docs" -TargetDir "/mnt/data/archive"
Linux‑style paths – works on PowerShell Core.
#>

param(
    [Parameter(Mandatory=$true)]
    [string]$SourceDir,
    [Parameter(Mandatory=$true)]
    [string]$TargetDir,
    [string]$OutputFile = "~matched_files.tsv"
)

# Validate directories exist
if (-not (Test-Path -Path $SourceDir -PathType Container)) {
    Write-Error "Source directory '$SourceDir' does not exist or is not a folder."
    exit 1
}
if (-not (Test-Path -Path $TargetDir -PathType Container)) {
    Write-Error "Target directory '$TargetDir' does not exist or is not a folder."
    exit 2
}

Write-Host "Collecting base names from source directory: $SourceDir" -ForegroundColor Cyan

# Get all files from source directory, extract unique base names (without extension)
try {
    $baseNames = Get-ChildItem -Path $SourceDir -File | ForEach-Object { $_.BaseName } | Sort-Object -Unique
} catch {
    Write-Error "Failed to read source directory: $_"
    exit 3
}

if ($baseNames.Count -eq 0) {
    Write-Warning "No files found in source directory. Exiting."
    exit 0
}

Write-Host "Found $($baseNames.Count) unique base names to search for." -ForegroundColor Green

# Search in target directory recursively
Write-Host "Searching in target directory: $TargetDir" -ForegroundColor Cyan
$results = @()

foreach ($name in $baseNames) {
    $matchingFiles = Get-ChildItem -Path $TargetDir -Recurse -File -ErrorAction SilentlyContinue | Where-Object {
        $_.BaseName -eq $name   # Exact, case‑insensitive match
    }
    
    foreach ($file in $matchingFiles) {
        $results += [PSCustomObject]@{
            SourceBaseName = $name
            FoundFilePath  = $file.FullName
        }
    }
}

# Build full output path inside $SourceDir
$outputPath = Join-Path -Path $SourceDir -ChildPath $OutputFile

# Export results as TSV (tab‑separated)
if ($results.Count -eq 0) {
    Write-Host "No matching files found in target directory." -ForegroundColor Yellow
    # Create an empty TSV file with headers only
    $emptyResult = [PSCustomObject]@{ SourceBaseName = ""; FoundFilePath = "" }
    $emptyResult | Export-Csv -Path $outputPath -Delimiter "`t" -NoTypeInformation
    Write-Host "Empty TSV file created at: $outputPath" -ForegroundColor DarkYellow
} else {
    $results | Export-Csv -Path $outputPath -Delimiter "`t" -NoTypeInformation
    Write-Host "`nFound $($results.Count) matching file(s)." -ForegroundColor Green
    Write-Host "Results saved to TSV file: $outputPath" -ForegroundColor Green
    Write-Host "`nFirst few results for preview:" -ForegroundColor Cyan
    $results | Select-Object -First 5 | Format-Table -AutoSize
}
