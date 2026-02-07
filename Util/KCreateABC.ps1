#!/usr/bin/env pwsh
<#
 .SYNOPSIS
	Create 26 new subfolders named as single letter from the set [A,Z]
 .DESCRIPTION
	The script will create folders A through Z in the specified base directory,
	skipping any that already exist, and provide detailed feedback about the operation.
 .PARAMETER BaseFolder
	The parent folder where the new subfolders will be created
 .EXAMPLE
	#Local folder (Windows) / (Linux)
	PS> .\KCreateABC.ps1 -BaseFolder "C:\MyFolders"
	pwsh KCreateABC.ps1 -BaseFolder "/home/user/MyFolders"
 .EXAMPLE
	#Relative path
	PS> .\KCreateABC.ps1 -BaseFolder ".\AlphabetFolders"
 .EXAMPLE
	#Network/UNC path (Windows) / Remote path (Linux SMB)
	PS> .\KCreateABC.ps1 -BaseFolder "\\server\share\AlphabetFolders"
	pwsh ./KCreateABC.ps1 -BaseFolder "//server/share/AlphabetFolders"
 .NOTES
	Help:
	PS> Get-Help ./KCreateABC.ps1 -full
 .NOTES
 	Run from PowerShell with the required parameter:
	.\KCreateABC.ps1 -BaseFolder "C:\YourTargetFolder"
	If you get execution policy errors, you can bypass it temporarily:
	(ref.: https:/go.microsoft.com/fwlink/?LinkID=135170)

	Change Execution Policy (One-time)
	Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
	.\KCreateABC.ps1 -BaseFolder "C:\YourTargetFolder"
 .NOTES
	- Works on both Windows and Linux PowerShell
	- Supports local paths, network shares (UNC paths), and relative paths
	- Can be run multiple times without creating duplicate folders
	- Shows which folders are being created and summary information

	Requirements:
	- PowerShell 6.0 or later (recommended for best cross-platform compatibility)
	- Appropriate permissions to create folders in the target location
	- Network connectivity for remote paths
 .OUTPUTS
	0: No error - The operation completed successfully.
	1: Fatal error - The operation failed due to a fatal error and did not complete.
#>

<#
	pwsh -ExecutionPolicy Bypass -File KCreateABC.ps1 -BaseFolder "C:\YourTargetFolder"
	The error 'pwsh' is not recognized indicates you're using Windows PowerShell
	(powershell.exe) rather than PowerShell Core (pwsh).
	Solution:
	a) Simply use powershell instead of pwsh:
	  powershell -ExecutionPolicy Bypass -File KCreateABC.ps1 -BaseFolder "C:\YourTargetFolder"
	b) Open PowerShell ISE, load the script, and run it.
	c) Unblock the file (if downloaded from internet)
	  Unblock-File -Path "KCreateABC.ps1" .\KCreateABC.ps1 -BaseFolder "C:\YourTargetFolder"
	d) Install PowerShell Core pwsh (Optional)
	- Download from Microsoft: https://github.com/PowerShell/PowerShell/releases
	- Windows Store: Search for "PowerShell"
	- Winget (Windows 10/11):
	  winget install Microsoft.PowerShell
	  apt (Ubuntu):
	  sudo apt-get install -y powershell
#>

param(
    [Parameter(Mandatory=$true)]
    [string]$BaseFolder
)

# Function to create alphabet folders
function KCreateABC {
    param(
        [string]$TargetPath
    )

    try {
        # Check if base folder exists, create if it doesn't
        if (-not (Test-Path -Path $TargetPath)) {
            Write-Host "Creating base folder: $TargetPath"
            New-Item -ItemType Directory -Path $TargetPath -Force | Out-Null
        }

        # Verify the path is actually a directory
        if (-not (Test-Path -Path $TargetPath -PathType Container)) {
            Write-Error "The path '$TargetPath' exists but is not a directory."
            return
        }

        Write-Host "Creating alphabet folders in: $TargetPath"

        # Create folders A through Z
        65..90 | ForEach-Object {
            $folderName = [char]$_
            $folderPath = Join-Path -Path $TargetPath -ChildPath $folderName

            if (-not (Test-Path -Path $folderPath)) {
                New-Item -ItemType Directory -Path $folderPath -Force | Out-Null
                Write-Host "Created folder: $folderName"
            } else {
                Write-Host "Folder already exists: $folderName"
            }
        }

        Write-Host "Alphabet folder creation completed successfully!" -ForegroundColor Green

        # Display summary
        $createdFolders = Get-ChildItem -Path $TargetPath -Directory | Where-Object { $_.Name -match '^[A-Z]$' }
        Write-Host "Total alphabet folders created/found: $($createdFolders.Count)" -ForegroundColor Cyan

    } catch {
        Write-Error "Error creating folders: $($_.Exception.Message)"
        exit 1
    }
}

# Main execution
try {
    Write-Host "Starting alphabet folder creation..." -ForegroundColor Yellow
    Write-Host "Base folder: $BaseFolder" -ForegroundColor Yellow

    # Handle both local and remote paths
    if ($BaseFolder -match '^\\\\' -or $BaseFolder -match '^//') {
        # UNC path (Windows network share)
        Write-Host "Detected network/UNC path" -ForegroundColor Cyan
    } elseif ($BaseFolder -match '^[a-zA-Z]:\\') {
        # Windows local path with drive letter
        Write-Host "Detected Windows local path" -ForegroundColor Cyan
    } else {
        # Linux/Mac path or relative path
        Write-Host "Detected Linux/Mac path or relative path" -ForegroundColor Cyan
    }

    # Create the alphabet folders
    KCreateABC -TargetPath $BaseFolder

} catch {
    Write-Error "Script execution failed: $($_.Exception.Message)"
    exit 1
}
