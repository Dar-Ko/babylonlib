<#
.SYNOPSIS
    Convert M4A audiofiles to FLAC format.

.DESCRIPTION
    Finds all M4A files with ALAC codecin the current directory and converts them to FLAC format.

.NOTES
    Prerequisites: FFmpeg installed on your system path

.NOTES
    On Windows, if execution is blocked by security policies, run 
      Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process
    in your PowerShell window first

.EXAMPLE
    Get-MySystemInfo -ComputerName "Server01" -Force

.OUTPUTS
    0: Success.
    1: No .m4a files found in the folder.
    2: FFmpeg is missing from the system PATH.
    3: Unhandled critical script exception.
#>

# Get all M4A files in the current folder
$files = Get-ChildItem -Filter *.m4a

if ($files.Count -eq 0) {
    Write-Host "No .m4a files found in this directory." -ForegroundColor Yellow
    exit 1
}

# Verify FFmpeg is installed before starting
if (-not (Get-Command ffmpeg -ErrorAction SilentlyContinue)) {
    Write-Host "Error: FFmpeg is required for conversion but was not found on your system PATH." -ForegroundColor Red
    Write-Host "Please install FFmpeg to proceed." -ForegroundColor Red
    exit 2
}

Write-Host "Checking M4A codec" -ForegroundColor Cyan
Write-Host "Scanning and converting only ALAC files..." -ForegroundColor Cyan
Write-Host "=========================================="

foreach ($file in $files) {
    try {
        # Open file as binary stream to read the header
        $stream = [System.IO.File]::OpenRead($file.FullName)
        $reader = New-Object System.IO.BinaryReader($stream)
        $bytes = $reader.ReadBytes(2000)
        $reader.Close()
        $stream.Close()

        # Convert binary data to ASCII string for pattern matching
        $headerString = [System.Text.Encoding]::ASCII.GetString($bytes)

        # Check for DRM Protection first (Apple FairPlay uses 'drms' or 'drmi' tokens)
        if ($headerString -match "drms" -or $headerString -match "drmi" -or $headerString -match "pasp") {
            Write-Host "[DRM Protected] " -NoNewline -ForegroundColor Magenta
            Write-Host "$($file.Name) -> Cannot convert protected iTunes files." -ForegroundColor DarkGray
            continue
        }

        # Process based on codec type
        # Check for ALAC Codec
        if ($headerString -match "alac") {
            Write-Host "[ALAC Detected] " -NoNewline -ForegroundColor Green
            Write-Host "$($file.Name) -> Converting to FLAC..." -ForegroundColor White

            # Define output filename (.flac)
            $outputFile = Join-Path $file.DirectoryName "$($file.BaseName).flac"

            # Run FFmpeg conversion (overwrites existing, copies metadata)
            # Capture FFmpeg error output to diagnose compression or corruption issues
            $ffmpegError =  & ffmpeg -y -i $file.FullName -c:a flac -map_metadata 0 $outputFile -loglevel error 2>&1

            if ($LASTEXITCODE -eq 0) {
                Write-Host "  ↳ Success: Created $($file.BaseName).flac" -ForegroundColor Green
            } else {
                Write-Host "  ↳ Failed: FFmpeg conversion error." -ForegroundColor Red
                Write-Host "    Reason: $ffmpegError" -ForegroundColor DarkRed

            }
        # Check for AAC Codec
        } elseif ($headerString -match "mp4a") {
            Write-Host "[AAC Skipped]   " -NoNewline -ForegroundColor Yellow
            Write-Host $file.Name
        } else {
            # Unknown format
            Write-Host "[Unknown Codec] " -NoNewline -ForegroundColor Red
            Write-Host $file.Name
        }
    }
    catch {
        Write-Host "[Error Reading] " -NoNewline -ForegroundColor Red
        Write-Host "$($file.Name) - $($_.Exception.Message)"
        exit 3
    }
}

Write-Host "`nProcess finished." -ForegroundColor Cyan
exit 0
