#!/bin/bash

# .SYNOPSIS
#    Installation script for Ubuntu 24.04+
# .USAGE
#    sudo ./installMyApps.sh
# .DESCRIPTION
#    This script installs a curated set of applications and tools on Ubuntu 24.04+.
# .NOTE
#    This script is intended for personal use and may require modifications for other environments.
#    Ensure the script runs with root privileges.
# .NOTE
#    Version: %VERSION-HASH%

if [ "$EUID" -ne 0 ]; then
  echo "Please run this script using sudo: sudo ./installMyApps.sh"
  exit 1
fi

echo "=========================================="
echo " Starting Expanded Application Setup"
echo "------------------------------------------"

# Refresh packages with new repositories active
apt update && apt upgrade -y

# 1. Native APT Loop
# If one package fails or changes upstream, the script will skip it and finish the rest.
apt_apps=(
    "7zip" "acetoneiso""asunder" "caja-actions" "cifs-utils" "curl" "dconf-editor" 
    "duplicity" "flatpak" "git" "gthumb" "keepassxc" 
    "krop" "meld" "naps2" "pavucontrol" "pdfarranger" 
    "qbittorrent" "remaster-iso" 
    "remmina" "remmina-plugin-rdp" "remmina-plugin-vnc" 
    "sayonara" "smplayer"
    "stacer" "vlc" "wget" "xchm"
)

echo "Installing native APT packages one-by-one..."
for app in "${apt_apps[@]}"; do
    echo "Installing: $app..."
    apt install -y "$app" || echo "ERROR: Failed to install $app, skipping..."
done

# 2. Snap Store Configurations
# ----------------------------
# --classic flag grants the application full access to your system's files
echo "Installing Snap applications..."
SNAP_OUTPUT=$(snap install code --classic 2>&1)         # Visual Studio Code
if [ $? -ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install gimp 2>&1)                   # GIMP GNU Image Manipulation Program
if [ $? -ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install joplin-desktop 2>&1)         # Joplin Note-Taking App
if [ $? -ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install opera 2>&1)                  # Opera Web Browser
if [ $? -ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install picard 2>&1)                 # MusicBrainz Picard 
if [ $? -ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install powershell --classic 2>&1)   # Microsoft PowerShell
if [ $? -ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install thunderbird 2>&1)            # Mozilla Thunderbird Email Client
if [ $? -ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install whatsapp-desktop-linux 2>&1) # WhatsApp Desktop Client
if [ $? -ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi

# 3. Flatpak Absolute Exceptions
# ------------------------------
echo "Configuring Flatpak..."
flatpak remote-add --if-not-exists flathub https://flathub.org
# Export the paths to the active terminal session
# This bypasses the need to reboot or log out for command-line access
export XDG_DATA_DIRS="/var/lib/flatpak/exports/share:$HOME/.local/share/flatpak/exports/share:$XDG_DATA_DIRS"

# Install Bottles for Wine/Proton compatibility
echo "Installing Bottles for Wine/Proton compatibility..."
flatpak install flathub com.usebottles.bottles -y

# Download and install Calibre
echo "Installing Calibre..."
flatpak install flathub com.calibre_ebook.calibre -y

# 4. Add downloaded .deb packages 
# -------------------------------
# Auto-Updates: Because you are manually downloading a static file URL instead
# of using a standard software repository, running a general system update
# (sudo apt upgrade) will not automatically update those package wrapper in the future.

mkdir -p /etc/apt/keyrings
# Ensure curl is installed for API access
if ! command -v curl &> /dev/null; then
    echo "Installing curl for API access..."
    apt install -y curl || echo "ERROR: Could not install curl."
fi

# AppImageLauncher Official Setup
echo "Installing AppImageLauncher..."
echo "AppImageLauncher: Installing FUSE 2 compatibility library for Ubuntu 24.04..."
apt install -y libfuse2t64 || echo "ERROR: Failed to install libfuse2t64, but continuing..."
# URL for the continuous build (bionic) .deb package
PACKAGE_URL="https://github.com/TheAssassin/AppImageLauncher/releases/download/v2.2.0/appimagelauncher_2.2.0-travis995.0f91801.bionic_amd64.deb"
PACKAGE_NAME="appimagelauncher.deb"
echo "Downloading the AppImageLauncher package..."
if wget -q -O "/tmp/$PACKAGE_NAME" "$PACKAGE_URL"; then
    echo "Installing /tmp/$PACKAGE_NAME..."
    if ! dpkg -i "/tmp/$PACKAGE_NAME"; then
        apt --fix-broken install -y
        dpkg -i "/tmp/$PACKAGE_NAME" || echo "ERROR: Failed to install $PACKAGE_NAME."
    fi
else
    echo "ERROR: Failed to download $PACKAGE_NAME"
fi

# balenaEtcher Setup
echo "Installing balenaEtcher..."
PACKAGE_URL="https://github.com/balena-io/etcher/releases/download/v1.19.25/balena-etcher_1.19.25_amd64.deb"
PACKAGE_NAME="balena-etcher_1.19.25_amd64.deb"
echo "Downloading the balenaEtcher package..."
if wget -q -O "/tmp/$PACKAGE_NAME" "$PACKAGE_URL"; then
    echo "Installing /tmp/$PACKAGE_NAME..."
    if ! dpkg -i "/tmp/$PACKAGE_NAME"; then
        apt --fix-broken install -y
        dpkg -i "/tmp/$PACKAGE_NAME" || echo "ERROR: Failed to install $PACKAGE_NAME."
    fi
else
    echo "ERROR: Failed to download $PACKAGE_NAME"
fi

# Dropbox Official Setup
echo "Installing Dropbox..."
PACKAGE_URL="https://www.dropbox.com/download?dl=packages/ubuntu/dropbox_2026.05.06_amd64.deb"
PACKAGE_NAME="dropbox_2026.05.06_amd64.deb"
echo "Downloading the Dropbox package..."
if wget -q -O "/tmp/$PACKAGE_NAME" "$PACKAGE_URL"; then
    echo "Installing /tmp/$PACKAGE_NAME..."
    if ! dpkg -i "/tmp/$PACKAGE_NAME"; then
        apt --fix-broken install -y
        dpkg -i "/tmp/$PACKAGE_NAME" || echo "ERROR: Failed to install $PACKAGE_NAME."
    fi
else
    echo "ERROR: Failed to download $PACKAGE_NAME"
fi

# FreeFileSync Official Setup
echo "Installing FreeFileSync..."
echo "FreeFileSync: Installing required dependencies..."
apt install -y libgtk-3-0 libwebkit2gtk-4.0-37 || echo "ERROR: Failed to install FreeFileSync dependencies."

# Download the official .run installer
FFS_VERSION="14.10" # Check for newer versions on the official website
FFS_URL="https://freefilesync.org/download/FreeFileSync_${FFS_VERSION}_Linux.tar.gz"
FFS_TAR_NAME="FreeFileSync_${FFS_VERSION}_Linux.tar.gz"
echo "Downloading the FreeFileSync package..."
if wget -q -O "/tmp/$FFS_TAR_NAME" "$FFS_URL"; then
    echo "Extracting /tmp/$FFS_TAR_NAME..."
    tar -xvf "/tmp/$FFS_TAR_NAME" -C /tmp/
    
    # Run the installer
    echo "Running the FreeFileSync installer..."
    cd "/tmp/FreeFileSync" || echo "ERROR: Failed to change directory."
    if [ -f "./FreeFileSync_${FFS_VERSION}_Install.run" ]; then
        # Unattended installation: accept license, install system-wide, skip desktop shortcuts
        ./FreeFileSync_${FFS_VERSION}_Install.run --accept-license --noshortcuts || echo "ERROR: FreeFileSync installation failed."
    else
        echo "ERROR: Installer script not found."
    fi
    cd ~
else
    echo "ERROR: Failed to download $FFS_TAR_NAME"
fi

# HandBrake Setup
echo "Installing HandBrake..."
echo "HandBrake: Adding the official PPA..."
add-apt-repository ppa:stebbins/handbrake-releases -y
# Updating package cache
apt update
apt install -y handbrake || echo "ERROR: Failed to install HandBrake."

# Jellyfin Setup 
echo "Installing Jellyfin Media Server..."
echo "Jellyfin: Adding the repository key..."
curl -fsSL https://repo.jellyfin.org/ubuntu/jellyfin_team.gpg.key | gpg --dearmor -o /usr/share/keyrings/jellyfin.gpg

echo "Jellyfin: Adding the repository..."
echo "deb [signed-by=/usr/share/keyrings/jellyfin.gpg] https://repo.jellyfin.org/ubuntu $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/jellyfin.list
# Updating package cache
apt update
apt install -y jellyfin || echo "ERROR: Failed to install Jellyfin."

# MEGA Sync Official Setup
echo "Installing MEGA Sync..."
# Download and install the MEGA signing key
curl -fsSL https://mega.nz/keys/MEGA_signing.key | gpg --dearmor -o /etc/apt/keyrings/meganz-archive-keyring.gpg
echo "deb [signed-by=/etc/apt/keyrings/meganz-archive-keyring.gpg] https://mega.nz/linux/repo/xUbuntu_24.04/ ./ " | tee /etc/apt/sources.list.d/megasync.list
# Updating package cache
apt update
apt install -y megasync || echo "ERROR: Failed to install MEGA Sync."

# NAPS2 Native APT Repository Setup
echo "Installing NAPS2 Not Another PDF Scanner 2..."
# Download the NAPS2 public key
curl -fsSL https://www.naps2.com/naps2-public.pgp | gpg --dearmor -o /etc/apt/keyrings/naps2.gpg
echo "deb [signed-by=/etc/apt/keyrings/naps2.gpg] https://downloads.naps2.com ./ " | tee /etc/apt/sources.list.d/naps2.list >/dev/null
# Updating package cache
apt update
apt install -y naps2 || echo "ERROR: Failed to install NAPS2."

# OpenClaw AI Assistant Setup
echo "Installing OpenClaw AI Assistant..."
echo "=========================================="
# Uses the official multi-platform setup deployment architecture for OpenClaw
# Install Node.js 22.x (required for OpenClaw)
curl -fsSL https://deb.nodesource.com/setup_22.x | bash -
apt install -y nodejs || echo "ERROR: Failed to install Node.js"
# Verify Node.js version
node --version
# npm is the package manager that is installed automatically as part of Node.js
echo "Installing OpenClaw by Node.js/npm..."
npm install -g openclaw@latest || echo "ERROR: Failed to install OpenClaw"

# ProtonVPN Official Setup
echo "Installing ProtonVPN..."
# Download the Proton VPN repository package
wget -q -O /tmp/protonvpn-stable-release.deb https://repo.protonvpn.com/debian/dists/stable/main/binary-all/protonvpn-stable-release_1.0.8_all.deb || echo "ERROR: Failed to download ProtonVPN repository package."
if [ -f /tmp/protonvpn-stable-release.deb ]; then
    dpkg -i /tmp/protonvpn-stable-release.deb && apt update || echo "ERROR: Failed to install ProtonVPN repository."
    
    echo "Installing ProtonVPN GUI application..."
    apt install -y proton-vpn-gnome-desktop || echo "ERROR: Failed to install ProtonVPN GUI application."
    
    # Optional: Install system tray icon extension for GNOME
    echo "Installing GNOME shell extension for system tray icon support..."
    apt install -y gnome-shell-extension-appindicator || echo "WARNING: Failed to install appindicator extension."
    
    # Clean up
    rm /tmp/protonvpn-stable-release.deb
else
    echo "ERROR: ProtonVPN repository package not downloaded. Skipping installation."
fi

# R-Linux Data Recovery Setup
echo "Installing R-Linux Data Recovery..."
PACKAGE_URL="https://www.r-studio.com/downloads/RLinux6_x64.deb"
PACKAGE_NAME="/tmp/rlinux.deb"
if wget -q -O "$PACKAGE_NAME" "$PACKAGE_URL"; then
    # Installing R-Linux from $PACKAGE_NAME"
    dpkg -i "$PACKAGE_NAME" || {
        # Fixing dependencies and retrying"
        apt --fix-broken install -y && dpkg -i "$PACKAGE_NAME"
    } || echo "ERROR: Failed to install R-Linux."
    rm "$PACKAGE_NAME" 2>/dev/null
else
    echo "ERROR: Failed to download R-Linux .deb package."
fi

# RustDesk Remote Desktop Setup
echo "Installing RustDesk..."
# Download the latest RustDesk .deb package from GitHub releases.
# GitHub API responds with JSON data, including a field named "browser_download_url".
PACKAGE_URL=$(curl -s https://api.github.com/repos/rustdesk/rustdesk/releases/latest 2>/dev/null | grep browser_download_url | grep 'x86_64.*\.deb' | cut -d '"' -f 4 | head -1)
# If API failed, use fallback version
if [ -z "$PACKAGE_URL" ]; then
    echo "WARNING: Failed to fetch RustDesk latest version."
    # Using fallback version 1.4.9
    PACKAGE_URL="https://github.com/rustdesk/rustdesk/releases/download/1.4.9/rustdesk-1.4.9-x86_64.deb"
fi
PACKAGE_NAME="/tmp/rustdesk.deb"
# Downloading RustDesk"
if wget -q -O "$PACKAGE_NAME" "$PACKAGE_URL"; then
    dpkg -i "$PACKAGE_NAME" || { 
        # Fixing dependencies and retrying"
        apt --fix-broken install -y && dpkg -i "$PACKAGE_NAME"
    } || echo "ERROR: Failed to install RustDesk."
    rm "$PACKAGE_NAME" 2>/dev/null
else
    echo "ERROR: Failed to download RustDesk .deb package."
fi

# SMPlayer Setup
echo "Installing SMPlayer..."
# Adding the official PPA for the latest version.
add-apt-repository ppa:alex-p/smplayer -y
# Updating package cache
apt update
apt install -y smplayer smplayer-themes || echo "ERROR: Failed to install SMPlayer."

# TailScale zero-config mesh networking setup
echo "Installing Tailscale..."
# Add Tailscale's package signing key and repository
curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/noble.noarmor.gpg | sudo tee /usr/share/keyrings/tailscale-archive-keyring.gpg >/dev/null
curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/noble.tailscale-keyring.list | sudo tee /etc/apt/sources.list.d/tailscale.list
apt update
apt install -y tailscale || echo "ERROR: Failed to install Tailscale."

# Viber Setup
echo "Installing Viber Desktop..."
# Download the official Viber .deb package from Viber's CDN
PACKAGE_URL="https://download.cdn.viber.com/cdn/desktop/Linux/viber.deb"
PACKAGE_NAME="/tmp/viber.deb"

if wget -q -O "$PACKAGE_NAME" "$PACKAGE_URL"; then
    # Try installing with apt first (better dependency handling)
    if ! apt install -y "$PACKAGE_NAME" 2>/dev/null; then
        # Fallback to dpkg with dependency fix
        dpkg -i "$PACKAGE_NAME" || {
            apt --fix-broken install -y && dpkg -i "$PACKAGE_NAME"
        } || echo "ERROR: Failed to install Viber."
    fi
    rm "$PACKAGE_NAME" 2>/dev/null
else
    echo "ERROR: Failed to download Viber .deb package."
fi

# ZeroTier zero-config mesh networking setup
echo "Installing ZeroTier..."
# Install ZeroTier using the official one-line installer
curl -s https://install.zerotier.com | bash
# Check if installation was successful
if ! command -v zerotier-cli &> /dev/null; then
    echo "ERROR: ZeroTier installation failed."
fi

# 7. Standalone Portable Setup (AppImage)
echo "Setting up Portable Applications Directory..."
mkdir -p /opt/AppImages

# 8. Force Ubuntu's GNOME desktop shell to refresh its application menu grid
# This makes the icons appear instantly without logging out
gsettings set org.gnome.desktop.app-folders folder-children "['Utilities']" 2>/dev/null || true


echo "------------------------------------------"
echo " Installation process finished! "
echo "=========================================="
echo "Manual tasks left:"
echo "1. Dropbox will launch automatically. Sign in to start syncing."
echo "2. FreeFileSync: Add .desktop files to your application menu manually if needed."
echo "3. Start and enable Jellyfin service"
echo "4. OpenClaw: Run 'openclaw onboard --install-daemon' in the terminal to initialize config variables and sync asset folders."
echo "4.1. OpenClaw Quick Start:"
echo "  1. Dashboard:   openclaw dashboard"
echo "  2. Status:      openclaw gateway status"
echo "  3. Test agent:  openclaw agent --message \"Hello!\""
echo "  4. Reconfigure: openclaw onboard"
echo "  OpenClaw documentation: https://openclaw.ai"
echo "5. ProtonVPN: Launch the GUI and sign in to your account."
echo "6. RustDesk: Launch the application and configure your remote desktop settings."
echo "7. Tailscale: Run 'sudo tailscale up' to authenticate and connect to your network."
echo "8. ZeroTier: Run 'sudo zerotier-cli join <network-id>' to connect to your ZeroTier network."
