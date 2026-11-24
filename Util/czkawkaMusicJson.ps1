#!/usr/bin/env pwsh

<#
.SYNOPSIS
    Compares duplicate audio files and merges differences using additional applications.
.DESCRIPTION
    Parses Czkawka's results_same_music_pretty.json, logs and skips groups with more than files,
    and invokes a helper script to compare or merge every duplicate pair.
    It will stop the execution if an error occurs.
.EXAMPLE
    chmod +x mergeAudioMetadata czkawkaMusicJson.ps1
    .\czkawkaMusicJson.ps1 -JsonPath "~\path\to\results_same_music_pretty.json"
.NOTES
    Requires a helper script to compare and merge metadata of two audio files.
    The script creates log file czkawka_skipped_groups.log

.NOTES
    Date:    2026-11-17
    Version: %VERSION-HASH%
#>
param (
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$JsonPath,

    [Parameter(Mandatory = $false)]
    [string]$MergeScriptPath = (Join-Path $PSScriptRoot "mergeAudioMetadata.ps1"),

    [Parameter(Mandatory = $false)]
    [string]$LogPath = (Join-Path $PSScriptRoot "czkawka_skipped_groups.log")
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path -LiteralPath $JsonPath)) {
    Write-Error "JSON file not found: $JsonPath"
    exit 403
}
if (-not (Test-Path -LiteralPath $MergeScriptPath)) {
    Write-Error "Phase 1 script not found at: $MergeScriptPath"
    exit 404
}

$rawJson = Get-Content -LiteralPath $JsonPath -Raw -Encoding UTF8 | ConvertFrom-Json

# Handle both top-level array [[{path:...}, {path:...}]] and wrapped object structures
$groups = @()
if ($rawJson -is [System.Array]) {
    $groups = $rawJson
} elseif ($rawJson.PSObject.Properties["similar_music"]) {
    $groups = $rawJson.similar_music
} else {
    foreach ($prop in $rawJson.PSObject.Properties) {
        if ($prop.Value -is [System.Array]) {
            $groups += $prop.Value
        }
    }
}

$totalGroups = $groups.Count
Write-Host "Loaded $totalGroups duplicate group(s) from '$JsonPath'." -ForegroundColor Cyan

$index = 0
foreach ($group in $groups) {
    $index++
    
    # Extract file paths from group items (supports objects with .path or plain strings)
    $paths = @()
    foreach ($item in $group) {
        if ($item -is [string]) {
            $paths += $item
        } elseif ($null -ne $item.path) {
            $paths += $item.path
        }
    }

    if ($paths.Count -gt 2) {
        $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
        $msg = "[$timestamp] WARNING: Group #$index has $($paths.Count) files (expected 2). Skipping:`n  - " + ($paths -join "`n  - ")
        Write-Warning "Group #$index has $($paths.Count) files. Logging and skipping to next item."
        Add-Content -LiteralPath $LogPath -Value "$msg`n" -Encoding UTF8
        continue
    }

    if ($paths.Count -lt 2) {
        Write-Warning "Group #$index has fewer than 2 files ($($paths.Count)). Skipping."
        continue
    }

    Write-Host "`n========================================================" -ForegroundColor DarkGray
    Write-Host "Processing Group #$index of $totalGroups" -ForegroundColor Yellow
    Write-Host "--------------------------------------------------------" -ForegroundColor DarkGray

    & $MergeScriptPath -File1 $paths[0] -File2 $paths[1]
}

Write-Host "`nAll groups processed. Any >2 file warnings were logged to: $LogPath" -ForegroundColor Green
