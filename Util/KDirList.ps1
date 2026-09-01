#!/usr/bin/env pwsh
<#
.SYNOPSIS
    Creates index files (TSV format) for directories recursively
.DESCRIPTION
    This script traverses directories from a starting path and creates _Index.tsv files
    containing directory contents. Directories that already have any file ending with
    "Index.tsv" are skipped.
.PARAMETER StartPath
    The starting directory path (defaults to current directory)
.EXAMPLE
    .\KDirList.ps1
    .\KDirList.ps1 -StartPath "C:\Users\Documents"
#>

param(
    [Parameter(Mandatory=$false)]
    [string]$StartPath = (Get-Location).Path
)

# Resolve the full path
$StartPath = Resolve-Path $StartPath -ErrorAction Stop

Write-Host "Starting directory indexing from: $StartPath" -ForegroundColor Green

###############################################################################
# Function to check if directory already has an Index.tsv file
function Has-IndexFile {
    param([string]$DirectoryPath)

    # Check for any file ending with "Index.tsv" in the directory
    $indexFiles = Get-ChildItem -Path $DirectoryPath -File | Where-Object { $_.Name -like "*Index.tsv" }
    return ($indexFiles.Count -gt 0)
}

###############################################################################
# Function to create index file for a directory
function New-DirectoryIndex {
    param([string]$DirectoryPath)

    try {
        # Get all items in the directory (excluding the index file we're about to create)
        $items = Get-ChildItem -Path $DirectoryPath | Where-Object {
            $_.Name -notlike "*Index.tsv" -and $_.Name -ne "_Index.tsv"
        }

        if ($items.Count -eq 0) {
            Write-Host "  Directory is empty, creating empty index" -ForegroundColor Yellow
        }

        # Create the index content
        $indexContent = @()
        $indexContent += "Storage`tDirectory`tFile Name`tDescription`tOperating System`tCategory`tVersion"
        foreach ($item in $items) {
            if ($item.PSIsContainer) {
                # Items is a directory
                $name = $item.Name + "\"
            }
            else {
                # Item is a file
                $name = $item.Name
            }

            $indexContent += "ID`t\`t$name`t`t`t`t"
        }

        # Save to file
        $indexFilePath = Join-Path $DirectoryPath "_Index.tsv"
        $indexContent | Out-File -FilePath $indexFilePath -Encoding UTF8

        Write-Host "  Created index with $($items.Count) items" -ForegroundColor Green
        return $true
    }
    catch {
        Write-Host "  Error creating index: $_" -ForegroundColor Red
        return $false
    }
}

###############################################################################
# Main execution
$processedCount = 0
$skippedCount = 0
$errorCount = 0

# Process all directories recursively
Get-ChildItem -Path $StartPath -Directory -Recurse | ForEach-Object {
    $dirPath = $_.FullName
    Write-Host "Checking: $dirPath" -ForegroundColor Cyan

    if (Has-IndexFile -DirectoryPath $dirPath) {
        Write-Host "  Skipping - already has an Index.tsv file" -ForegroundColor Yellow
        $skippedCount++
    }
    else {
        Write-Host "  Creating index..." -ForegroundColor Green
        if (New-DirectoryIndex -DirectoryPath $dirPath) {
            $processedCount++
        }
        else {
            $errorCount++
        }
    }
}

# Process the starting directory itself
Write-Host "`nProcessing root directory: $StartPath" -ForegroundColor Cyan

if (Has-IndexFile -DirectoryPath $StartPath) {
    Write-Host "  Skipping - already has an Index.tsv file" -ForegroundColor Yellow
    $skippedCount++
}
else {
    Write-Host "  Creating index..." -ForegroundColor Green
    if (New-DirectoryIndex -DirectoryPath $StartPath) {
        $processedCount++
    }
    else {
        $errorCount++
    }
}

# Summary
Write-Host "`n=== Indexing Complete ===" -ForegroundColor Green
Write-Host "Directories processed: $processedCount" -ForegroundColor Green
Write-Host "Directories skipped: $skippedCount" -ForegroundColor Yellow
if ($errorCount -gt 0) {
    Write-Host "Errors encountered: $errorCount" -ForegroundColor Red
}