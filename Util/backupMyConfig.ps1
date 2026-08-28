#!/usr/bin/pwsh

<#
.SYNOPSIS
    Backs up user data and configuration files for an Ubuntu downgrade.
.DESCRIPTION
    This script creates a timestamped backup of critical user data, including
    application configs, SSH keys, and personal documents. It also generates
    a list of installed packages for reinstallation after downgrade.
    Intended to be run on Ubuntu MATE 26.04 before downgrading to 24.04.
    The script saves the backup to /home/backup and creates a log file (backup.log).
    The restoration process will involve copying these files back to their
    original locations.
.PARAMETER IncludeUserDirs
    Optional switch to include user directories (Documents, Downloads, etc.) in the backup.
    Default is false. Use -IncludeUserDirs to include them.
.EXAMPLE
    chmod +x backupMyConfig.ps1
    sudo --preserve-env=PATH pwsh ./backupMyConfig.ps1
    # to restore packages:
    sudo dpkg --set-selections < installed-packages.txt
    sudo apt-get dselect-upgrade
    # to restore  Snap packages:
    while read -r line; do
        snap install $line
    done < installed-snaps.txt
.NOTES
    Backups of system configurations:
    PPAs and repositories (APT sources /etc/apt/sources.list and sources.list.d/)
    Cron Jobs (system and user crontabs)
    NetworkManager Connections
    CUPS Printer configurations
    SSH Host Keys (/etc/ssh/)
    Samba State (/var/lib/samba/)
.NOTES
    The script generates package lists for:
    installed-packages.txt - Complete package list with selection states (install/deinstall)
    installed-packages-with-versions.txt - Detailed list with version numbers
    manually-installed-packages.txt - Only packages manually installed (not dependencies)
    installed-snaps.txt - List of installed Snap packages (if Snap is installed)
    installed-flatpaks.txt - List of installed Flatpak packages (if Flatpak is installed)
    installed-appimages.txt - List of installed AppImage applications
.NOTES
    Date:    2026-08-14
    Version: %VERSION-HASH%
#>

param(
    [switch]$IncludeUserDirs = $false
)

# --- Configuration ---
# DETECT THE REAL USER (even when running with sudo)
if ($env:SUDO_USER) {
    # Running with sudo - get the real user
    $REAL_USER = $env:SUDO_USER
    $USER_HOME = "/home/$REAL_USER"
    Write-Host "Detected sudo: Running as root, but real user is: $REAL_USER" -ForegroundColor Yellow
    Write-Host "Using home directory: $USER_HOME" -ForegroundColor Yellow
} else {
    # Running as normal user
    $REAL_USER = $env:USER
    $USER_HOME = $env:HOME
    Write-Host "Running as normal user: $REAL_USER" -ForegroundColor Green
    Write-Host "Using home directory: $USER_HOME" -ForegroundColor Green
}

$BACKUP_BASE = "/home/backup"
$TIMESTAMP = Get-Date -Format "yyyyMMdd_HHmmss"
$BACKUP_DIR = Join-Path -Path $BACKUP_BASE -ChildPath "ubuntu_config_backup_$TIMESTAMP"
$BACKUP_LOG = Join-Path -Path $BACKUP_DIR -ChildPath "backup.log"

# --- CREATE BACKUP DIRECTORY FIRST ---
New-Item -ItemType Directory -Path $BACKUP_DIR -Force | Out-Null
New-Item -ItemType File -Path $BACKUP_LOG -Force | Out-Null

try {
    # Force PowerShell to render colors as ANSI sequences even when not in
    # an interactive terminal. Otherwise redirecting to stdout will make PowerShell
    # strip color codes.
    $global:PSStyle.OutputRendering = 'Ansi'
} catch {
    Write-Host "$([char]0x1b)[31m✗ PSStyle ForegroundColor failed: $_ $([char]0x1b)[0m"
    # Fallback for older PowerShell
    Write-Host "$([char]0x1b)[33m PowerShell ver. $($PSVersionTable.PSVersion) $([char]0x1b)[0m"
    $env:TERM = 'xterm-256color'
}

# --- Helper to log events ---
function Write-Log {
    param(
        [string]$Message,
        [ConsoleColor]$ForegroundColor = [ConsoleColor]::White
    )

    $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    $logEntry = "[$timestamp] $Message"
    Write-Host $logEntry -ForegroundColor $ForegroundColor
    Add-Content -Path $BACKUP_LOG -Value $logEntry
}

# --- Helper function to handle wildcard paths ---
function Copy-Items {
    param(
        [string]$SourcePath,
        [string]$DestinationRoot
    )
    
    Read-Host "(109) Check if $SourcePath is a file. Press Enter to continue"
   
    # Check if it's a specific file with an extension (not a wildcard)
    if (Test-Path $SourcePath -PathType Leaf) {
        # It's a specific file - copy it directly
        $relativePath = $SourcePath.TrimStart('/')
        $dest = Join-Path -Path $DestinationRoot -ChildPath $relativePath
        $destDir = Split-Path -Path $dest -Parent
        
        Write-Log "  Source file: $SourcePath" -ForegroundColor Gray
        Write-Log "  Dest file: $dest" -ForegroundColor Gray
        
        Write-Log "    Relative: $relativePath" -ForegroundColor Gray
        Write-Log "    Dest Dir: $destDir" -ForegroundColor Gray

        New-Item -ItemType Directory -Path $destDir -Force -ErrorAction SilentlyContinue
        if (-not (Test-Path $destDir)) {
            Write-Log "  ✗ ERROR (126): Failed to create directory: $destDir" -ForegroundColor Red
            return $false
        }
        Copy-Item -Path $SourcePath -Destination $dest -Force -ErrorAction SilentlyContinue
        
        if ($?) {
            Write-Log "  ✓ Copied successfully (132)" -ForegroundColor Green
            return $true
        } else {
            Write-Log "  ✗ ERROR (135): Failed to copy" -ForegroundColor Red
            return $false
        }
    }

    Read-Host "(140) Press Enter to continue" 

    # Check if the path contains wildcard characters
    if ($SourcePath -match '[*?\[\]]') {
        # Split path into directory and pattern
        $directory = Split-Path -Path $SourcePath -Parent
        $pattern = Split-Path -Path $SourcePath -Leaf
        
        # Check if directory exists
        if (-not (Test-Path $directory)) {
            Write-Log "  ⚠ Warning (146): Directory '$directory' not found, skipping wildcard pattern." -ForegroundColor Yellow
            return $false
        }
        
        Read-Host "(150) Press Enter to continue" 

        # Build the destination directory (preserve path structure)
        $relativeDir = $directory.TrimStart('/')
        $destDir = Join-Path -Path $DestinationRoot -ChildPath $relativeDir
        New-Item -ItemType Directory -Path $destDir -Force | Out-Null
        
        # Get matching files
        $matchingFiles = Get-ChildItem -Path $SourcePath -ErrorAction SilentlyContinue
        
        if (-not $matchingFiles -or $matchingFiles.Count -eq 0) {
            Write-Log "  ⚠ Warning ($($MyInvocation.ScriptLineNumber)): No files matching pattern '$pattern' in '$directory'" -ForegroundColor Yellow
            return $false
        }
        
        Write-Log "  Found $($matchingFiles.Count) file(s) matching pattern '$pattern'"
        
        # Copy each matching file
        $copiedCount = 0
        foreach ($file in $matchingFiles) {
            if ($file.PSIsContainer) {
                # If it's a directory, copy recursively
                $destSubDir = Join-Path -Path $destDir -ChildPath $file.Name
                Copy-Item -Path $file.FullName -Destination $destSubDir -Recurse -Force 2>/dev/null
            } else {
                # Copy file
                Copy-Item -Path $file.FullName -Destination $destDir -Force 2>/dev/null
            }
            
            if ($?) {
                $copiedCount++
                Write-Log "    ✓ Copied: $($file.Name) (185)" -ForegroundColor Green
            } else {
                Write-Log "    ✗ ERROR (187): Failed to copy: $($file.Name)" -ForegroundColor Red
            }
        }
        
        Write-Log "  ✓ Copied $copiedCount of $($matchingFiles.Count) items"
        return $true
    } else {
        # No wildcard - use standard copy
        if (Test-Path $SourcePath) {
            Read-Host "(196) Test-Path $SourcePath. Press Enter to continue"

            $relativePath = $SourcePath.TrimStart('/')
            $dest = Join-Path -Path $DestinationRoot -ChildPath $relativePath
            $destDir = Split-Path -Path $dest -Parent
            New-Item -ItemType Directory -Path $destDir -Force | Out-Null
            
            if (Test-Path $SourcePath -PathType Container) {
                Copy-Item -Path $SourcePath -Destination $dest -Recurse -Force 2>/dev/null
            } else {
                Copy-Item -Path $SourcePath -Destination $dest -Force 2>/dev/null
            }
            
            if ($?) {
                Write-Log "  ✓ Copied successfully (210)" -ForegroundColor Green
                return $true
            } else {
                Write-Log "  ✗ ERROR: Failed to copy" -ForegroundColor Red
                return $false
            }
        } else {
            Write-Log "  ⚠ Warning (210): $SourcePath not found, skipping." -ForegroundColor Yellow
            return $false
        }
    }
}

# -----------------------------------------------------------
# --- Helper function to copy 1-tier directory structure only
function Copy-DirNames {
    param(
        [string]$SourcePath,
        [string]$DestinationRoot,
        [string]$Description = "directory"
    )
    
    if (-not (Test-Path $SourcePath)) {
        Write-Log "  ⚠ Warning ($($MyInvocation.ScriptLineNumber)): Source path '$SourcePath' not found, skipping." -ForegroundColor Yellow
        return $false
    }
    
    # Create destination directory
    $relativePath = $SourcePath.TrimStart('/')
    $destBase = Join-Path -Path $DestinationRoot -ChildPath $relativePath
    New-Item -ItemType Directory -Path $destBase -Force | Out-Null
    
    Write-Log "  Backing up first-level $Description from $SourcePath"
    
    # Get all items at the first level (non-recursive)
    $items = Get-ChildItem -Path $SourcePath -ErrorAction SilentlyContinue
    
    if (-not $items -or $items.Count -eq 0) {
        Write-Log "  ⚠ No items found in $SourcePath" -ForegroundColor Yellow
        return $true
    }
    
    $copiedCount = 0
    $totalCount = $items.Count
    
    foreach ($item in $items) {
        $destItem = Join-Path -Path $destBase -ChildPath $item.Name
        
        if ($item.PSIsContainer) {
            # It's a directory - copy only the directory structure (empty folder)
            Write-Log "    Creating directory: $($item.Name)/"
            New-Item -ItemType Directory -Path $destItem -Force | Out-Null
            $copiedCount++
        } else {
            # It's a file - copy the file
            Write-Log "    Copying file: $($item.Name)"
            Copy-Item -Path $item.FullName -Destination $destItem -Force 2>/dev/null
            if ($?) {
                $copiedCount++
            } else {
                Write-Log "      ✗ ERROR: Failed to copy $($item.Name)" -ForegroundColor Red
            }
        }
    }
    
    Write-Log "  ✓ Copied $copiedCount of $totalCount first-level items from $SourcePath"
    return $true
}

# -----------------------------------------------------------
# --- Helper function to find AppImages in common locations and generate a list
function Get-AppImages {
    param(
        [string]$SearchPath,
        [string]$OutputFile
    )
    
    Write-Log "  Searching for AppImages in: $SearchPath"
    
    # Common AppImage locations
    $appImagePaths = @(
        "$SearchPath/Applications/*.AppImage",
        "$SearchPath/Applications/*.appimage",
        "$SearchPath/*.AppImage",
        "$SearchPath/*.appimage",
        "$SearchPath/.local/bin/*.AppImage",
        "$SearchPath/.local/bin/*.appimage",
        "$SearchPath/bin/*.AppImage",
        "$SearchPath/bin/*.appimage",
        "$SearchPath/Downloads/*.AppImage",
        "$SearchPath/Downloads/*.appimage",
        "$SearchPath/Desktop/*.AppImage",
        "$SearchPath/Desktop/*.appimage"
    )
    
    $allAppImages = @()
    $foundPaths = @()
    
    foreach ($pattern in $appImagePaths) {
        $matchingFiles = Get-ChildItem -Path $pattern -ErrorAction SilentlyContinue
        foreach ($file in $matchingFiles) {
            if (-not $file.PSIsContainer) {
                # Check if it's actually an AppImage (has executable bit or magic bytes)
                $isAppImage = $false
                
                # Method 1: Check file command output
                $fileType = & file -b $file.FullName 2>/dev/null
                if ($fileType -match "ELF.*executable|AppImage") {
                    $isAppImage = $true
                }
                
                # Method 2: Check for AppImage magic bytes
                if (-not $isAppImage) {
                    $bytes = [System.IO.File]::ReadAllBytes($file.FullName)[0..7] -join ' '
                    if ($bytes -match "7f 45 4c 46") {  # ELF magic
                        $isAppImage = $true
                    }
                }
                
                # Method 3: Check if it has execute permissions and is a regular file
                if (-not $isAppImage) {
                    $perms = (Get-Item $file.FullName).UnixMode
                    if ($perms -match "x" -and $file.Length -gt 10MB) {
                        # Likely an executable, check if it's an AppImage by running --appimage-extract test
                        try {
                            $test = & $file.FullName --appimage-help 2>&1 | Out-String
                            if ($test -match "AppImage") {
                                $isAppImage = $true
                            }
                        } catch {
                            # Silently continue - not all AppImages support --appimage-help
                        }
                    }
                }
                
                if ($isAppImage) {
                    $appImageInfo = [PSCustomObject]@{
                        Path = $file.FullName
                        Name = $file.Name
                        Size = $file.Length
                        Modified = $file.LastWriteTime
                        Permissions = $file.UnixMode
                    }
                    $allAppImages += $appImageInfo
                    $foundPaths += $file.FullName
                    Write-Log "    ✓ Found AppImage: $($file.Name)"
                }
            }
        }
    }
    
    # Also check for AppImages in common application directories
    $commonAppDirs = @(
        "$SearchPath/.AppImages",
        "$SearchPath/.local/share/appimages",
        "$SearchPath/AppImages",
        "/opt/appimages",
        "/usr/local/appimages"
    )
    
    foreach ($dir in $commonAppDirs) {
        if (Test-Path $dir) {
            $appImages = Get-ChildItem -Path "$dir/*.AppImage", "$dir/*.appimage" -ErrorAction SilentlyContinue
            foreach ($file in $appImages) {
                if (-not $file.PSIsContainer -and $file.FullName -notin $foundPaths) {
                    $appImageInfo = [PSCustomObject]@{
                        Path = $file.FullName
                        Name = $file.Name
                        Size = $file.Length
                        Modified = $file.LastWriteTime
                        Permissions = $file.UnixMode
                    }
                    $allAppImages += $appImageInfo
                    $foundPaths += $file.FullName
                    Write-Log "    ✓ Found AppImage: $($file.Name)"
                }
            }
        }
    }
    
    # Remove duplicates
    $allAppImages = $allAppImages | Sort-Object -Property Path -Unique
    
    if ($allAppImages.Count -eq 0) {
        Write-Log "  ℹ No AppImages found in $SearchPath"
        return $false
    }
    
    # Write to output file
    Write-Log "  Found $($allAppImages.Count) AppImage(s)"
    
    $header = "# AppImage List - Generated $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')`n"
    $header += "# User: $REAL_USER`n"
    $header += "# Total AppImages: $($allAppImages.Count)`n"
    $header += "# `n"
    $header += "# Format: NAME|PATH|SIZE(MB)|MODIFIED|PERMISSIONS`n"
    $header += "# " + "-" * 70 + "`n"
    
    $content = $header
    foreach ($app in $allAppImages | Sort-Object -Property Name) {
        $sizeMB = [math]::Round($app.Size / 1MB, 2)
        $content += "$($app.Name)|$($app.Path)|$sizeMB MB|$($app.Modified)|$($app.Permissions)`n"
    }
    
    # Add restoration instructions
    $content += "`n# RESTORATION INSTRUCTIONS:`n"
    $content += "# To restore these AppImages after downgrade, copy them back to their original locations:`n"
    $content += "#   sudo cp -r /path/to/backup/appimages/* /original/path/`n"
    $content += "#   chmod +x /path/to/AppImage (if needed)`n"
    
    $content | Out-File -FilePath $OutputFile -Encoding UTF8
    
    # Also create a simple list of just paths (for easy copying)
    $pathList = "$($OutputFile).paths"
    $allAppImages | ForEach-Object { $_.Path } | Out-File -FilePath $pathList -Encoding UTF8
    
    return $true
}

# -----------------------------------------------------------
# --- Start of Script ---
Write-Log "========================================" -ForegroundColor Cyan
Write-Host "Starting backup configuration..." -ForegroundColor Cyan
Write-Host "Backup will be stored in: $BACKUP_DIR" -ForegroundColor Yellow
Write-Host "User home directory: $USER_HOME" -ForegroundColor Yellow
Write-Host "Real username: $REAL_USER" -ForegroundColor Yellow

# Create the backup and log directories
New-Item -ItemType Directory -Path $BACKUP_DIR -Force | Out-Null
New-Item -ItemType File -Path $BACKUP_LOG -Force | Out-Null

Write-Log "--- Backup Process Started ---"
Write-Log "Real User: $REAL_USER"
Write-Log "Home directory: $USER_HOME"
if ($env:SUDO_USER) {
    Write-Log "Running with sudo (elevated privileges for system files)"
} else {
    Write-Log "Running without sudo (normal user privileges)"
}

Read-Host "(441) Press Enter to continue"

# --- Generate Package List ---
Write-Log "Generating list of installed packages..."
$PACKAGE_LIST_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "installed-packages.txt"
try {
    dpkg --get-selections > $PACKAGE_LIST_FILE 2>&1
    if ($LASTEXITCODE -eq 0) {
        Write-Log "Package list saved to: $PACKAGE_LIST_FILE"
    } else {
        Write-Log "ERROR: Failed to generate package list" -ForegroundColor Red
    }
    
    # Also generate a more detailed list with versions (optional but helpful)
    $PACKAGE_DETAILED_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "installed-packages-with-versions.txt"
    dpkg -l > $PACKAGE_DETAILED_FILE 2>&1
    Write-Log "Detailed package list with versions saved to: $PACKAGE_DETAILED_FILE"
    
    # Generate list of manually installed packages (not dependencies)
    $MANUAL_PACKAGES_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "manually-installed-packages.txt"
    apt-mark showmanual > $MANUAL_PACKAGES_FILE 2>&1
    Write-Log "Manually installed packages list saved to: $MANUAL_PACKAGES_FILE"
    
    # Generate list of installed snaps (if snap is used)
    if (Get-Command snap -ErrorAction SilentlyContinue) {
        $SNAP_LIST_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "installed-snaps.txt"
        snap list > $SNAP_LIST_FILE 2>&1
        Write-Log "Installed snaps list saved to: $SNAP_LIST_FILE"
    }

    # Generate list of installed flatpaks
    if (Get-Command flatpak -ErrorAction SilentlyContinue) {
        $FLATPAK_LIST_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "installed-flatpaks.txt"
        flatpak list --app > $FLATPAK_LIST_FILE 2>&1
        Write-Log "Installed flatpaks list saved to: $FLATPAK_LIST_FILE"
    }

    # Generate list of installed AppImages
    Write-Log "Generating list of installed AppImages..."
    $APPIMAGE_LIST_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "installed-appimages.txt"
    
    # Search in user's home directory and common locations
    $appImageFound = Get-AppImages -SearchPath $USER_HOME -OutputFile $APPIMAGE_LIST_FILE
    
    if ($appImageFound) {
        Write-Log "AppImage list saved to: $APPIMAGE_LIST_FILE"
        Write-Log "  Also saved as: $APPIMAGE_LIST_FILE.paths (just the paths)"
    } else {
        Write-Log "No AppImages found on the system" -ForegroundColor Yellow
        # Create an empty file with note
        "No AppImages found on the system (searched in $USER_HOME and common locations)" | 
            Out-File -FilePath $APPIMAGE_LIST_FILE -Encoding UTF8
    }

} catch {
    Write-Log "ERROR: Failed to generate package lists: $_" -ForegroundColor Red
}

# --- Backup Application Configurations ---
Write-Log "Backing up application configurations..."

# 1. Browser and Email Configurations
$appDirs = @(
    ".config/autostart",    # Autostart applications
    ".config/keepassxc/keepassxc.ini", # KeepassXC config    
    ".config/mpv",          # Celluloid (formerly MPV) media player configs
    ".config/MusicBrainz",  # Picard config 
    "snap/picard/current/.config/MusicBrainz/Picard", # Picard plugins for Snap
    "snap/picard/current/.config/MusicBrainz/Picard.ini", # Picard config for Snap
    ".config/rustdesk",     # RustDesk
    ".cert",                # Custom certificates
    ".face",                # User face/avatar for login
    ".gnupg",               # GnuPG keys and configs
    ".joplin",              # Joplin (assuming default location)
    "snap/joplin-desktop/current/.config", # Joplin config for Snap
    ".local/share/mime/packages", # Custom MIME types
    ".mozilla",             # Firefox
    "snap/firefox/common/.mozilla", # Firefox config for Snap
    ".pam_environment",     # PAM environment variables
    ".ssh",                 # SSH keys and configs
    ".thunderbird",         # Thunderbird
    "snap/thunderbird/common/.thunderbird", # Thunderbird config for Snap
    ".zerotier-one",        # ZeroTier
    "Documents/CommonSoft.loz",        # CommonSoft documents (example)
    "Projects/babylonlib/.git",        # BabylonLib project git config
    "Templates"             # User Office templates directory

)

foreach ($item in $appDirs) {
    $src = Join-Path -Path $USER_HOME -ChildPath $item
    Write-Log "Checking for: $src"
    $result = Copy-Items -SourcePath $src -DestinationRoot $BACKUP_DIR
        
    if ($result -and $env:SUDO_USER) {
        # Ensure correct ownership (use real user, not root)
        $destPath = Split-Path (Join-Path -Path $BACKUP_DIR -ChildPath $item)
        # Only chown if the destination actually exists
        if (Test-Path $destPath) {
            chown -R "${REAL_USER}:${REAL_USER}" $destPath 2>/dev/null
            if ($LASTEXITCODE -ne 0) {
                Write-Log "  ⚠ Warning (551): Could not fix ownership for $destPath" -ForegroundColor Yellow
            }
        }
    }
   
}

<#
foreach ($dir in $appDirs) {
    $src = Join-Path -Path $USER_HOME -ChildPath $dir
    Write-Log "Checking for: $src"
    if (Test-Path $src) {
        $dest = Join-Path -Path $USER_BACKUP_DIR -ChildPath $dir
        Write-Log "Copying $src to $dest"
        # Ensure correct ownership (use real user, not root)
        Copy-Item -Path $src -Destination $dest -Recurse -Force
        if ($?) {
            Write-Log "  ✓ Copied successfully"
            # Fix ownership if running as sudo
            if ($env:SUDO_USER) {
                chown -R "${REAL_USER}:${REAL_USER}" $dest 2>/dev/null
                if ($LASTEXITCODE -ne 0) {
                    Write-Log "  ⚠ Warning: Could not fix ownership for $dest" -ForegroundColor Yellow
                }
            }
        } else {
            Write-Log "  ✗ ERROR: Failed to copy" -ForegroundColor Red
        }
    } else {
        Write-Log "  ⚠ Warning: $src not found, skipping." -ForegroundColor Yellow
    }
}
#>
# 2. System Configuration Files (requires sudo)
Write-Log "Backing up system configuration files (requires sudo)..."

$appAdmin = @(
    "/etc/apt/sources.list",                  # APT sources
    "/etc/apt/sources.list.d",                # APT sources list directory
    "/etc/.credentials",                      # Custom credentials (if exists)
    "/etc/crontab",                           # Cron jobs (user and system)
    "/etc/cron.d",
    "/etc/cups",                              # CUPS printer configs
    "/etc/default/grub",                      # GRUB configuration
    "/etc/fstab",                             # Filesystem table (for CFIS mounts)    
    "/etc/hosts",                             # Hosts file
    "/etc/modprobe.d/alsa-base.conf",         # ALSA sound configuration
    "/etc/modprobe.d/blacklist.conf",         # Module blacklist
    "/etc/modprobe.d/disable-nvidia-hdmi.conf", # Disable NVIDIA HDMI audio
    "/etc/modprobe.d/hda-denylist.conf",      # Denylist for HDA audio
    "/etc/modprobe.d/hda-intel-force.conf",   # Force HDA Intel driver
    "/etc/NetworkManager/system-connections", # NetworkManager connections
    "/etc/nsswitch.conf",                     # Name service switch configuration (wins)
    "/etc/rc.local",                          # rc.local script
    "/etc/samba/smb.conf",                    # Samba configuration
    "/etc/ssh",                               # SSH host keys
    "/etc/sudoers.d",                         # Sudoers configuration
    "/var/lib/samba",                         # Samba user/domain info if Samba is a DC (if exists)
    "/etc/X11/xorg.conf.d/*.conf",            # X11 configuration files
    "/var/lib/zerotier-one/identity.*"        # ZeroTier One ID    
)

# Process regular paths
Write-Log "`nProcessing standard system paths..."
foreach ($item in $appAdmin) {
    Write-Log "Checking for: $item"
    Copy-Items -SourcePath $item -DestinationRoot $BACKUP_DIR
}

# --- Backup /mnt/ directory structure (if exists) ---
Copy-DirNames -SourcePath "/mnt" -DestinationRoot $BACKUP_DIR -Description "mnt mount point"

# Backup user crontab (as the real user, not root)
Write-Log "Backing up user crontab (if exists)..."
$USER_CRON_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "crontab-user.txt"
if ($env:SUDO_USER) {
    # Run crontab as the real user
    sudo -u $REAL_USER crontab -l > $USER_CRON_FILE 2>&1
} else {
    crontab -l > $USER_CRON_FILE 2>&1
}
if ($LASTEXITCODE -eq 0) {
    Write-Log "  ✓ User crontab saved to: $USER_CRON_FILE"
} else {
    Write-Log "  ℹ No user crontab found or error retrieving it." -ForegroundColor Yellow
}

# --- Define user directories ---
$userDirs = @(
    "Documents",
    "Public",
    "Music",
    "Downloads",
    "Pictures",
    "Templates",
    "Videos"
)

# --- Backup User Directories ---
if ($IncludeUserDirs) {
    Write-Log "---------------------------------------"
    Write-Log "BACKING UP USER DIRECTORIES"
    Write-Log "---------------------------------------"

    foreach ($dir in $userDirs) {
        $src = Join-Path -Path $USER_HOME -ChildPath $dir
        Write-Log "Checking for user directory: $src"
        
        if (Test-Path $src) {
            $dest = Join-Path -Path $BACKUP_DIR -ChildPath $dir
            Write-Log "  ✓ Found! Copying $src to $dest"
            
            # Get size before copy for logging
            $sizeBefore = (Get-ChildItem -Path $src -Recurse -File -ErrorAction SilentlyContinue | Measure-Object -Property Length -Sum).Sum
            if ($sizeBefore) {
                $sizeMB = [math]::Round($sizeBefore / 1MB, 2)
                Write-Log "  Directory size: $sizeMB MB"
            }
            
            Copy-Item -Path $src -Destination $dest -Recurse -Force -ErrorAction Continue
            
            if ($?) {
                Write-Log "  ✓ Copied successfully!"
                
                # Fix ownership if running as sudo
                if ($env:SUDO_USER) {
                    chown -R "${REAL_USER}:${REAL_USER}" $dest 2>/dev/null
                    if ($LASTEXITCODE -ne 0) {
                        Write-Log "  ⚠ Warning: Could not fix ownership for $dest" -ForegroundColor Yellow
                    }
                }
                
                # Verify copy
                if (Test-Path $dest) {
                    $sizeAfter = (Get-ChildItem -Path $dest -Recurse -File -ErrorAction SilentlyContinue | Measure-Object -Property Length -Sum).Sum
                    if ($sizeAfter) {
                        $sizeAfterMB = [math]::Round($sizeAfter / 1MB, 2)
                        Write-Log "  ✓ Verified: $sizeAfterMB MB copied"
                    }
                    Write-Log "  ✓ Destination: $dest"
                }
            } else {
                Write-Log "  ✗ ERROR: Failed to copy $src" -ForegroundColor Red
            }
        } else {
            Write-Log "  ⚠ Warning ($($MyInvocation.ScriptLineNumber)): $src not found, skipping." -ForegroundColor Yellow
            # List what's actually in the home directory for debugging
            if ($dir -eq "Documents") {
                Write-Log "  Contents of ${USER_HOME}:"
                Get-ChildItem -Path $USER_HOME -ErrorAction SilentlyContinue | ForEach-Object {
                    Write-Log "    - $($_.Name)"
                }
            }
        }
    }
} else {
    Write-Log "User directories skipped (use -IncludeUserDirs to include them)" -ForegroundColor Yellow
}

# --- Final Summary ---
Write-Log "----------------------------------------" -ForegroundColor Cyan
Write-Log "--- Backup Process Completed ---"         -ForegroundColor Cyan
Write-Log "========================================" -ForegroundColor Cyan
Write-Log "Backup stored in: $BACKUP_DIR"
Write-Log "Log file: $BACKUP_LOG"

# Display summary of generated files
Write-Host "`n=== Generated Backup Files ===" -ForegroundColor Cyan
if (Test-Path $BACKUP_DIR) {
    $items = Get-ChildItem -Path $BACKUP_DIR -Recurse -File -ErrorAction SilentlyContinue
    if ($items) {
        $totalSize = 0
        $items | ForEach-Object {
            $relativePath = $_.FullName.Substring($BACKUP_DIR.Length + 1)
            $sizeKB = [math]::Round($_.Length / 1KB, 2)
            $totalSize += $_.Length
            Write-Host "  $relativePath ($sizeKB KB)" -ForegroundColor Gray
        }
        $totalMB = [math]::Round($totalSize / 1MB, 2)
        Write-Host "`n  Total backup size: $totalMB MB" -ForegroundColor Yellow
    } else {
        Write-Host "  No files found in backup directory!" -ForegroundColor Red
    }
}

# Check if user directories were backed up
if ($IncludeUserDirs) {
    Write-Host "`n=== User Directory Backup Status ===" -ForegroundColor Cyan
    foreach ($dir in $userDirs) {
        $dest = Join-Path -Path $BACKUP_DIR -ChildPath $dir
        if (Test-Path $dest) {
            $size = (Get-ChildItem -Path $dest -Recurse -File -ErrorAction SilentlyContinue | Measure-Object -Property Length -Sum).Sum
            if ($size) {
                $sizeMB = [math]::Round($size / 1MB, 2)
                Write-Host "  ✓ $dir : $sizeMB MB" -ForegroundColor Green
            } else {
                Write-Host "  ✓ $dir : (empty directory)" -ForegroundColor Green
            }
        } else {
            Write-Host "  ✗ $dir : NOT BACKED UP" -ForegroundColor Red
        }
    }
} else {
    Write-Host "`n=== User Directory Backup Status ===" -ForegroundColor Cyan
    Write-Host "  User directories were skipped (use -IncludeUserDirs to backup)" -ForegroundColor Yellow
}

# Display AppImage information
$APPIMAGE_LIST_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "installed-appimages.txt"
if (Test-Path $APPIMAGE_LIST_FILE) {
    $appImageCount = (Get-Content $APPIMAGE_LIST_FILE | Where-Object { $_ -match '\.AppImage|\.appimage' }).Count
    if ($appImageCount -gt 0) {
        Write-Host "`n=== AppImage Backup Status ===" -ForegroundColor Cyan
        Write-Host "  ✓ Found $appImageCount AppImage(s)" -ForegroundColor Green
        Write-Host "  List saved to: installed-appimages.txt" -ForegroundColor Gray
        Write-Host "  Paths only: installed-appimages.txt.paths" -ForegroundColor Gray
    }
}

Write-Host "`nBackup complete. Please ensure the backup directory is saved to an external drive before proceeding with the downgrade." -ForegroundColor Green
Write-Host "Package lists generated. To reinstall packages after downgrade, use:" -ForegroundColor Yellow
Write-Host "  sudo dpkg --set-selections < installed-packages.txt" -ForegroundColor Yellow
Write-Host "  sudo apt-get dselect-upgrade" -ForegroundColor Yellow
Write-Host "`nTo reinstall AppImages after downgrade:" -ForegroundColor Yellow
Write-Host "  cp installed-appimages.txt.paths /path/to/restore/" -ForegroundColor Yellow
Write-Host "  chmod +x /path/to/restore/*.AppImage" -ForegroundColor Yellow
Write-Host "`nIMPORTANT: Since you ran with sudo, backup files in $BACKUP_DIR" -ForegroundColor Yellow
Write-Host "may be owned by root. To fix ownership after backup:" -ForegroundColor Yellow
Write-Host "  sudo chown -R ${REAL_USER}:${REAL_USER} $BACKUP_DIR" -ForegroundColor Yellow
