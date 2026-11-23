#!/usr/bin/env pwsh

<#
.SYNOPSIS
    Compares and merges metadata of two audio files using Meld or Beyond Compare,
    optionally backs up the target file, and updates the target in-place without re-encoding.
.EXAMPLE
    .\mergeAudioMetadata.ps1 -File1 "D:\Music\track_a.flac" -File2 "D:\Music\track_b.mp3"
.NOTES
    Requires PowerShell 7+ (Ubuntu 24.04) and PowerShell 5.1+ (Windows).
.NOTES
    Date:    2026-11-17
    Version: %VERSION-HASH%
#>
param (
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$File1,

    [Parameter(Mandatory = $true, Position = 1)]
    [string]$File2
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path -LiteralPath $File1)) { Write-Error "File not found: $File1"; exit 1 }
if (-not (Test-Path -LiteralPath $File2)) { Write-Error "File not found: $File2"; exit 1 }

# 1. Locate Meld or Beyond Compare (Cross-platform: Windows & Ubuntu)
if ($IsLinux) {
    $diffTool = @("bcompare", "meld") | ForEach-Object { (Get-Command $_ -ErrorAction SilentlyContinue).Source } | Select-Object -First 1
} else {
    $candidates = @(
        "$env:ProgramFiles\Beyond Compare 5\BCompare.exe",
        "$env:ProgramFiles\Beyond Compare 4\BCompare.exe",
        "$env:ProgramFiles (x86)\Meld\Meld.exe",
        "$env:ProgramFiles\Meld\Meld.exe",
        "$env:LOCALAPPDATA\Programs\Meld\Meld.exe"
    )
    $diffTool = $candidates | Where-Object { Test-Path $_ } | Select-Object -First 1
    if (-not $diffTool) {
        $diffTool = @("bcompare", "meld") | ForEach-Object { (Get-Command $_ -ErrorAction SilentlyContinue).Source } | Select-Object -First 1
    }
}

if (-not $diffTool) {
    Write-Error "Neither Beyond Compare nor Meld was found. Please install one and ensure it is accessible."
    exit 1
}

# Helper: Extract ffmetadata and sort tag lines alphabetically so keys line up in diff view
function Export-SortedMetadata {
    param ([string]$AudioPath, [string]$OutTxt)
    $rawTxt = "$OutTxt.raw"
    & ffmpeg -y -v error -i $AudioPath -f ffmetadata $rawTxt
    $lines = Get-Content -LiteralPath $rawTxt -Encoding UTF8
    $header = $lines | Where-Object { $_ -eq ";FFMETADATA1" }
    $tags = $lines | Where-Object { $_ -ne ";FFMETADATA1" -and $_ -match "=" } | Sort-Object
    @($header) + @($tags) | Set-Content -LiteralPath $OutTxt -Encoding UTF8
    Remove-Item -LiteralPath $rawTxt -ErrorAction SilentlyContinue
}

$tmpDir = [System.IO.Path]::GetTempPath()
$guid = [Guid]::NewGuid().ToString("N").Substring(0, 8)
$tag1 = Join-Path $tmpDir "1_${guid}_$([System.IO.Path]::GetFileNameWithoutExtension($File1)).txt"
$tag2 = Join-Path $tmpDir "2_${guid}_$([System.IO.Path]::GetFileNameWithoutExtension($File2)).txt"

try {
    Export-SortedMetadata -AudioPath $File1 -OutTxt $tag1
    Export-SortedMetadata -AudioPath $File2 -OutTxt $tag2

    $hash1Before = (Get-FileHash -LiteralPath $tag1).Hash
    $hash2Before = (Get-FileHash -LiteralPath $tag2).Hash

    Write-Host "`nOpening diff tool..." -ForegroundColor Cyan
    Write-Host "  [Left]  $File1"
    Write-Host "  [Right] $File2"
    Write-Host "Merge tags into the side you want to update, press Ctrl+S, and close the diff window.`n"

    Start-Process -FilePath $diffTool -ArgumentList @("`"$tag1`"", "`"$tag2`"") -Wait

    $hash1After = (Get-FileHash -LiteralPath $tag1).Hash
    $hash2After = (Get-FileHash -LiteralPath $tag2).Hash

    # 2. Detect which side was edited and saved
    if ($hash1Before -ne $hash1After -and $hash2Before -ne $hash2After) {
        Write-Warning "Both metadata files were modified! Which audio file should receive the merged metadata?"
        $choice = Read-Host "Enter [1] for Left ($File1), [2] for Right ($File2), or [C] to cancel"
        if ($choice -eq "1") { $targetAudio = $File1; $mergedTags = $tag1 }
        elseif ($choice -eq "2") { $targetAudio = $File2; $mergedTags = $tag2 }
        else { Write-Host "Cancelled." -ForegroundColor Yellow; exit 0 }
    }
    elseif ($hash1Before -ne $hash1After) {
        $targetAudio = $File1
        $mergedTags = $tag1
    }
    elseif ($hash2Before -ne $hash2After) {
        $targetAudio = $File2
        $mergedTags = $tag2
    }
    else {
        Write-Host "No changes were saved in the diff tool. Skipping file update." -ForegroundColor Yellow
        exit 0
    }

    Write-Host "Target file selected for update: $targetAudio" -ForegroundColor Green

    # 3. Offer to back up the target file
    $backupChoice = Read-Host "Save a backup copy (.bak) of the target file before overwriting? [Y/n]"
    if ($backupChoice -notmatch "^[Nn]$") {
        $backupPath = "$targetAudio.bak"
        Copy-Item -LiteralPath $targetAudio -Destination $backupPath -Force
        Write-Host "Backup saved to: $backupPath" -ForegroundColor Cyan
    }

    # 4. Write merged metadata into a temporary audio file, then replace the target in-place
    $dir = [System.IO.Path]::GetDirectoryName((Resolve-Path -LiteralPath $targetAudio).Path)
    $ext = [System.IO.Path]::GetExtension($targetAudio)
    $tempAudioOut = Join-Path $dir "temp_merged_${guid}${ext}"

    & ffmpeg -y -v error -i $targetAudio -i $mergedTags -map 0 -map_metadata 1 -c copy $tempAudioOut

    if (Test-Path -LiteralPath $tempAudioOut) {
        Move-Item -LiteralPath $tempAudioOut -Destination $targetAudio -Force
        Write-Host "Successfully saved merged metadata to: $targetAudio" -ForegroundColor Green
    } else {
        Write-Error "FFmpeg failed to generate the updated audio file. Original file was not touched."
    }
}
finally {
    Remove-Item -LiteralPath $tag1, $tag2 -ErrorAction SilentlyContinue
}

