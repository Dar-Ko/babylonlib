#!/usr/bin/env pwsh

<#
.SYNOPSIS
List the codec of all M4A files in the current folder.

.DESCRIPTION
Verifies if a M4a file is ALAC Lossless or AAC Lossy audio codec.
ALAC (Apple Lossless Audio Codec) matches CD quality up to high-resolution 24-bit/192 kHz.
AAC (Advanced Audio Coding) removes inaudible audio details to shrink file size.

.NOTES
On Windows, if execution is blocked by security policies, run in your PowerShell
window following command before running the script:
    Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process

.NOTES
    Date:    2026-06-01
    Version: %VERSION-HASH%
#>

# Get all M4A files in the current folder
# Prerequisites: FFmpeg installed on your system path
# Note: 
$files = Get-ChildItem -Filter *.m4a

if ($files.Count -eq 0) {
    Write-Host "No .m4a files found in this directory." -ForegroundColor Yellow
    exit
}

Write-Host "Checking M4A files..." -ForegroundColor Cyan
Write-Host "======================"

foreach ($file in $files) {
    try {
        # Open the file as a binary stream to read the header
        $stream = [System.IO.File]::OpenRead($file.FullName)
        $reader = New-Object System.IO.BinaryReader($stream)
        
        # Read the first 2000 bytes to scan for the codec atom signature
        $bytes = $reader.ReadBytes(2000)
        $reader.Close()
        $stream.Close()
        
        # Convert binary data to an ASCII string for pattern matching
        $headerString = [System.Text.Encoding]::ASCII.GetString($bytes)
        
        # Check the signature atoms inside the MP4 container
        if ($headerString -match "alac") {
            Write-Host "[ALAC Lossless] " -NoNewline -ForegroundColor Green
            Write-Host $file.Name
        } elseif ($headerString -match "mp4a") {
            Write-Host "[AAC Lossy]     " -NoNewline -ForegroundColor Yellow
            Write-Host $file.Name
        } else {
            Write-Host "[Unknown Codec] " -NoNewline -ForegroundColor Red
            Write-Host $file.Name
        }
    }
    catch {
        Write-Host "[Error Reading] " -NoNewline -ForegroundColor Red
        Write-Host "$($file.Name) - $($_.Exception.Message)"
    }
}
