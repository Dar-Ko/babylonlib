<# 
.SYNOPSIS
    Converts all OGG files in a specified directory to FLAC format using FFmpeg.
.PARAMETER SourceDirectory
    Directory containing OGG files to convert
.NOTES
    Prerequisites:
    - PWS Version 6.0
    - FFmpeg installed on your system path

.NOTES
    Date:    2026-06-01
    Version: %VERSION-HASH%

.EXAMPLE
   #Convert current folder:
   .\KOggToFlac.ps1
   #Convert a specific folder:
   .\KOggToFlac.ps1 -SourceDirectory "/path/to/your/music"
#>
param (
    [string]$SourceDirectory = "."
)

# Grab all .ogg files in the specified directory
$OggFiles = Get-ChildItem -Path $SourceDirectory -Filter *.ogg

if ($OggFiles.Count -eq 0) {
    Write-Host "No .ogg files found in '$SourceDirectory'." -ForegroundColor Yellow
    Exit 1
}

# Check if FFmpeg is installed on the system path
if (-not (Get-Command ffmpeg -ErrorAction SilentlyContinue)) {
    Write-Error "Error: 'ffmpeg' is not installed or not found in your system PATH."
    Write-Host "Please install FFmpeg before running this script."
    Exit 2
}

Write-Host "Found $($OggFiles.Count) files to convert.`n" -ForegroundColor Cyan

# Iterate and convert each file
foreach ($File in $OggFiles) {
    try {

        # Generate the matching destination path with a .flac extension
        $FlacPath = Join-Path -Path $File.DirectoryName -ChildPath "$($File.BaseName).flac"
        
        Write-Host "Converting: $($File.Name) -> $($File.BaseName).flac" -ForegroundColor White
        
        # Run FFmpeg to convert audio (-c:a flac) and clone all metadata (-map_metadata 0)
        & ffmpeg -y -i $File.FullName -c:a flac -map_metadata 0 $FlacPath -nostats -loglevel error
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "Successfully converted: $($File.BaseName).flac" -ForegroundColor Green
        } else {
            Write-Error "Failed to convert file: $($File.Name)"
        }
    }
    catch {
        Write-Host "[Error Reading] " -NoNewline -ForegroundColor Red
        Write-Host "$($file.Name) - $($_.Exception.Message)"
    }
}

Write-Host "`nAll operations complete!" -ForegroundColor Cyan
