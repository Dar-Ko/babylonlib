#!/usr/bin/pwsh

<#
.SYNOPSIS
    Backs up user data and configuration files for an Ubuntu downgrade.
.DESCRIPTION
    This script creates a timestamped backup of critical user data, including
    application configs, SSH keys, and personal documents. It also generates
    a list of installed packages for reinstallation after downgrade.
    Intended to be run on Ubuntu MATE 26.04 before downgrading to 24.04.
.NOTES
    Date:   October 26, 2023
    Version: 2.0 - Fixed user directory backup issue
#>

# --- Configuration ---
$USER_HOME = $env:HOME
$BACKUP_BASE = "/home/backup"
$TIMESTAMP = Get-Date -Format "yyyyMMdd_HHmmss"
$BACKUP_DIR = Join-Path -Path $BACKUP_BASE -ChildPath "ubuntu_downgrade_backup_$TIMESTAMP"
$BACKUP_LOG = Join-Path -Path $BACKUP_DIR -ChildPath "backup.log"

# --- Start of Script ---
Write-Host "Starting backup for downgrade from Ubuntu 26.04 to 24.04..." -ForegroundColor Cyan
Write-Host "Backup will be stored in: $BACKUP_DIR" -ForegroundColor Yellow
Write-Host "User home directory: $USER_HOME" -ForegroundColor Yellow

# Create the backup and log directories
New-Item -ItemType Directory -Path $BACKUP_DIR -Force | Out-Null
New-Item -ItemType File -Path $BACKUP_LOG -Force | Out-Null

function Log-Message {
    param([string]$Message)
    $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    $logEntry = "[$timestamp] $Message"
    Write-Host $logEntry
    Add-Content -Path $BACKUP_LOG -Value $logEntry
}

Log-Message "--- Backup Process Started ---"
Log-Message "User: $env:USER"
Log-Message "Home directory: $USER_HOME"

# --- Generate Package List ---
Log-Message "Generating list of installed packages..."
$PACKAGE_LIST_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "installed-packages.txt"
try {
    dpkg --get-selections > $PACKAGE_LIST_FILE 2>&1
    if ($LASTEXITCODE -eq 0) {
        Log-Message "Package list saved to: $PACKAGE_LIST_FILE"
    } else {
        Log-Message "ERROR: Failed to generate package list"
    }
    
    # Also generate a more detailed list with versions (optional but helpful)
    $PACKAGE_DETAILED_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "installed-packages-with-versions.txt"
    dpkg -l > $PACKAGE_DETAILED_FILE 2>&1
    Log-Message "Detailed package list with versions saved to: $PACKAGE_DETAILED_FILE"
    
    # Generate list of manually installed packages (not dependencies)
    $MANUAL_PACKAGES_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "manually-installed-packages.txt"
    apt-mark showmanual > $MANUAL_PACKAGES_FILE 2>&1
    Log-Message "Manually installed packages list saved to: $MANUAL_PACKAGES_FILE"
    
    # Generate list of installed snaps (if snap is used)
    if (Get-Command snap -ErrorAction SilentlyContinue) {
        $SNAP_LIST_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "installed-snaps.txt"
        snap list > $SNAP_LIST_FILE 2>&1
        Log-Message "Installed snaps list saved to: $SNAP_LIST_FILE"
    }
} catch {
    Log-Message "ERROR: Failed to generate package lists: $_"
}

# --- Backup Application Configurations ---
Log-Message "Backing up application configurations..."

# 1. Browser and Email Configurations
$appDirs = @(
    ".mozilla",      # Firefox
    ".thunderbird",  # Thunderbird
    ".config/rustdesk", # RustDesk
    ".config/MusicBrainz", # Picard config 
    ".joplin",       # Joplin (assuming default location)
    ".zerotier-one"  # ZeroTier
)

foreach ($dir in $appDirs) {
    $src = Join-Path -Path $USER_HOME -ChildPath $dir
    Log-Message "Checking for: $src"
    if (Test-Path $src) {
        $dest = Join-Path -Path $BACKUP_DIR -ChildPath $dir
        Log-Message "Copying $src to $dest"
        Copy-Item -Path $src -Destination $dest -Recurse -Force
        Log-Message "  ✓ Copied successfully"
    } else {
        Log-Message "  ✗ Warning: $src not found, skipping."
    }
}

# 2. System Configuration Files (requires sudo)
Log-Message "Backing up system configuration files (requires sudo)..."

# Backup Samba configuration
if (Test-Path "/etc/samba/smb.conf") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc/samba"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    Log-Message "Copying /etc/samba/smb.conf to $dest"
    sudo cp /etc/samba/smb.conf "$dest/smb.conf.bak"
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied successfully"
    } else {
        Log-Message "  ✗ ERROR: Failed to copy"
    }
} else {
    Log-Message "Warning: /etc/samba/smb.conf not found, skipping."
}

# Backup hosts file
if (Test-Path "/etc/hosts") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    Log-Message "Copying /etc/hosts to $dest"
    sudo cp /etc/hosts "$dest/hosts.bak"
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied successfully"
    } else {
        Log-Message "  ✗ ERROR: Failed to copy"
    }
} else {
    Log-Message "Warning: /etc/hosts not found, skipping."
}

# Backup CFIS mount (this is a placeholder, adjust as needed)
# CFIS mounts are often defined in /etc/fstab or as systemd units.
# Backup fstab as a starting point.
if (Test-Path "/etc/fstab") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    Log-Message "Copying /etc/fstab to $dest"
    sudo cp /etc/fstab "$dest/fstab.bak"
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied successfully"
    } else {
        Log-Message "  ✗ ERROR: Failed to copy"
    }
    Log-Message "Note: Review $dest/fstab.bak for CFIS mount entries."
}

# Backup /etc/apt/sources.list and sources.list.d (important for re-adding repos)
Log-Message "Backing up APT sources..."
if (Test-Path "/etc/apt/sources.list") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc/apt"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    sudo cp /etc/apt/sources.list "$dest/sources.list.bak"
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied /etc/apt/sources.list to $dest"
    } else {
        Log-Message "  ✗ ERROR: Failed to copy sources.list"
    }
}
if (Test-Path "/etc/apt/sources.list.d") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc/apt/sources.list.d"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    sudo cp -r /etc/apt/sources.list.d/* "$dest/" 2>/dev/null
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied /etc/apt/sources.list.d to $dest"
    } else {
        Log-Message "  ✗ ERROR: Failed to copy sources.list.d"
    }
}

# --- Backup SSH Keys ---
Log-Message "Backing up SSH keys..."
$sshSrc = Join-Path -Path $USER_HOME -ChildPath ".ssh"
if (Test-Path $sshSrc) {
    $sshDest = Join-Path -Path $BACKUP_DIR -ChildPath ".ssh"
    Log-Message "Copying $sshSrc to $sshDest"
    Copy-Item -Path $sshSrc -Destination $sshDest -Recurse -Force
    Log-Message "  ✓ Copied successfully"
} else {
    Log-Message "Warning: $sshSrc not found, skipping."
}

# --- Backup User Directories (FIXED) ---
Log-Message "========================================"
Log-Message "BACKING UP USER DIRECTORIES"
Log-Message "========================================"

$userDirs = @(
    "Documents",
    "Public",
    "Music",
    "Downloads",
    "Pictures",
    "Templates",
    "Videos"
)

foreach ($dir in $userDirs) {
    $src = Join-Path -Path $USER_HOME -ChildPath $dir
    Log-Message "Checking for user directory: $src"
    
    if (Test-Path $src) {
        $dest = Join-Path -Path $BACKUP_DIR -ChildPath $dir
        Log-Message "  ✓ Found! Copying $src to $dest"
        
        # Get size before copy for logging
        $sizeBefore = (Get-ChildItem -Path $src -Recurse -File -ErrorAction SilentlyContinue | Measure-Object -Property Length -Sum).Sum
        if ($sizeBefore) {
            $sizeMB = [math]::Round($sizeBefore / 1MB, 2)
            Log-Message "  Directory size: $sizeMB MB"
        }
        
        Copy-Item -Path $src -Destination $dest -Recurse -Force -ErrorAction Continue
        
        if ($LASTEXITCODE -eq 0 -or $?) {
            Log-Message "  ✓ Copied successfully!"
            
            # Verify copy
            if (Test-Path $dest) {
                $sizeAfter = (Get-ChildItem -Path $dest -Recurse -File -ErrorAction SilentlyContinue | Measure-Object -Property Length -Sum).Sum
                if ($sizeAfter) {
                    $sizeAfterMB = [math]::Round($sizeAfter / 1MB, 2)
                    Log-Message "  ✓ Verified: $sizeAfterMB MB copied"
                }
                Log-Message "  ✓ Destination: $dest"
            }
        } else {
            Log-Message "  ✗ ERROR: Failed to copy $src"
        }
    } else {
        Log-Message "  ✗ Warning: $src not found, skipping."
        # List what's actually in the home directory for debugging
        if ($dir -eq "Documents") {
            Log-Message "  Contents of $USER_HOME:"
            Get-ChildItem -Path $USER_HOME -ErrorAction SilentlyContinue | ForEach-Object {
                Log-Message "    - $($_.Name)"
            }
        }
    }
}

# --- Backup /etc/ssh for host keys (important for re-adding to network) ---
Log-Message "Backing up SSH host keys..."
if (Test-Path "/etc/ssh") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc/ssh"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    Log-Message "Copying /etc/ssh to $dest"
    sudo cp -r /etc/ssh/* "$dest/" 2>/dev/null
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied successfully"
    } else {
        Log-Message "  ✗ ERROR: Failed to copy"
    }
} else {
    Log-Message "Warning: /etc/ssh not found, skipping."
}

# --- Backup /var/lib/samba for user/domain info if Samba is a DC ---
Log-Message "Backing up Samba state (if exists)..."
if (Test-Path "/var/lib/samba") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "var/lib/samba"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    Log-Message "Copying /var/lib/samba to $dest"
    sudo cp -r /var/lib/samba/* "$dest/" 2>/dev/null
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied successfully"
    } else {
        Log-Message "  ✗ ERROR: Failed to copy"
    }
} else {
    Log-Message "Warning: /var/lib/samba not found, skipping."
}

# --- Backup Cron jobs (user and system) ---
Log-Message "Backing up cron jobs..."
if (Test-Path "/etc/crontab") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    sudo cp /etc/crontab "$dest/crontab.bak" 2>/dev/null
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied /etc/crontab to $dest"
    }
}
if (Test-Path "/etc/cron.d") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc/cron.d"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    sudo cp -r /etc/cron.d/* "$dest/" 2>/dev/null
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied /etc/cron.d to $dest"
    }
}

# Backup user crontab
Log-Message "Backing up user crontab (if exists)..."
$USER_CRON_FILE = Join-Path -Path $BACKUP_DIR -ChildPath "crontab-user.txt"
crontab -l > $USER_CRON_FILE 2>&1
if ($LASTEXITCODE -eq 0) {
    Log-Message "  ✓ User crontab saved to: $USER_CRON_FILE"
} else {
    Log-Message "  No user crontab found or error retrieving it."
}

# --- Backup Network Manager connections (if using NetworkManager) ---
Log-Message "Backing up NetworkManager connections..."
if (Test-Path "/etc/NetworkManager/system-connections") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc/NetworkManager/system-connections"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    sudo cp -r /etc/NetworkManager/system-connections/* "$dest/" 2>/dev/null
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied NetworkManager connections to $dest"
    }
} else {
    Log-Message "NetworkManager connections not found, skipping."
}

# --- Backup CUPS printers (if using printing) ---
Log-Message "Backing up CUPS printer configurations..."
if (Test-Path "/etc/cups/printers.conf") {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath "etc/cups"
    New-Item -ItemType Directory -Path $dest -Force | Out-Null
    sudo cp /etc/cups/printers.conf "$dest/printers.conf.bak" 2>/dev/null
    if ($LASTEXITCODE -eq 0) {
        Log-Message "  ✓ Copied CUPS printers.conf to $dest"
    }
} else {
    Log-Message "CUPS printers.conf not found, skipping."
}

# --- Final Summary ---
Log-Message "========================================"
Log-Message "--- Backup Process Completed ---"
Log-Message "========================================"
Log-Message "Backup stored in: $BACKUP_DIR"
Log-Message "Log file: $BACKUP_LOG"

# Display summary of generated files
Write-Host "`n=== Generated Backup Files ===" -ForegroundColor Cyan
if (Test-Path $BACKUP_DIR) {
    $items = Get-ChildItem -Path $BACKUP_DIR -Recurse -File -ErrorAction SilentlyContinue
    if ($items) {
        $items | ForEach-Object {
            $relativePath = $_.FullName.Substring($BACKUP_DIR.Length + 1)
            $sizeKB = [math]::Round($_.Length / 1KB, 2)
            Write-Host "  $relativePath ($sizeKB KB)" -ForegroundColor Gray
        }
    } else {
        Write-Host "  No files found in backup directory!" -ForegroundColor Red
    }
}

# Check if user directories were backed up
Write-Host "`n=== User Directory Backup Status ===" -ForegroundColor Cyan
$userDirs | ForEach-Object {
    $dest = Join-Path -Path $BACKUP_DIR -ChildPath $_
    if (Test-Path $dest) {
        $size = (Get-ChildItem -Path $dest -Recurse -File -ErrorAction SilentlyContinue | Measure-Object -Property Length -Sum).Sum
        if ($size) {
            $sizeMB = [math]::Round($size / 1MB, 2)
            Write-Host "  ✓ $_ : $sizeMB MB" -ForegroundColor Green
        } else {
            Write-Host "  ✓ $_ : (empty directory)" -ForegroundColor Green
        }
    } else {
        Write-Host "  ✗ $_ : NOT BACKED UP" -ForegroundColor Red
    }
}

Write-Host "`nBackup complete. Please ensure the backup directory is saved to an external drive before proceeding with the downgrade." -ForegroundColor Green
Write-Host "Package lists generated. To reinstall packages after downgrade, use:" -ForegroundColor Yellow
Write-Host "  sudo dpkg --set-selections < installed-packages.txt" -ForegroundColor Yellow
Write-Host "  sudo apt-get dselect-upgrade" -ForegroundColor Yellow
