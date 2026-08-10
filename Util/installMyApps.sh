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

# Enable debug mode for extra verbosity
# set -x  # Uncomment this line for full command tracing
DEBUG_MODE="${DEBUG:-true}"  # Set DEBUG=true to enable debug tracing

DBG_TRACE() {
    if [ "$DEBUG_MODE" = "true" ]; then
        local message="${1:-Press Enter to continue...}"
        echo ""
        echo "🔍 DBG_TRACE: $message"
        read -p "Press Enter to continue..."
        echo ""
    fi
}

if [ "$EUID" -ne 0 ]; then
  echo "Please run this script using sudo: sudo ./installMyApps.sh"
  exit 1
fi

echo "=========================================="
echo " Starting Expanded Application Setup"
echo "------------------------------------------"
DBG_TRACE "0."
if false; then
# Refresh packages with new repositories active
apt update && apt upgrade -y

# 1. Native APT Loop
# If one package fails or changes upstream, the script will skip it and finish the rest.
apt_apps=(
    "7zip" "acetoneiso" "asunder" "caja-actions" "cifs-utils" "curl" "dconf-editor" 
    "duplicity" "flatpak" "git" "gthumb" "keepassxc" 
    "krop" "meld" "pavucontrol" "pdfarranger" 
    "qbittorrent" "remaster-iso" 
    "remmina" "remmina-plugin-rdp" "remmina-plugin-vnc" 
    "sayonara" 
    "stacer" "vlc" "wget" "xchm"
)

echo "Installing native APT packages one-by-one..."
for app in "${apt_apps[@]}"; do
    echo "Installing: $app..."
    apt install -y "$app" || echo "ERROR: Failed to install $app, skipping..."
    DBG_TRACE "1."
done

# 2. Snap Store Configurations
# ----------------------------
# --classic flag grants the application full access to your system's files
echo "Installing Snap applications..."
# Visual Studio Code
if ! SNAP_OUTPUT=$(snap install code --classic 2>&1); then
    echo "ERROR: $SNAP_OUTPUT"
else
    echo "✅ $SNAP_OUTPUT"
fi
DBG_TRACE "2.1"

# GIMP GNU Image Manipulation Program
if ! SNAP_OUTPUT=$(snap install gimp 2>&1); then
    echo "ERROR: $SNAP_OUTPUT"
else
    echo "✅ $SNAP_OUTPUT"
fi
DBG_TRACE "2.2"
# Joplin Note-Taking App
if ! SNAP_OUTPUT=$(snap install joplin-desktop 2>&1); then
    echo "ERROR: $SNAP_OUTPUT"
else
    echo "✅ $SNAP_OUTPUT"
fi
DBG_TRACE "2.3"
# Opera Web Browser
if ! SNAP_OUTPUT=$(snap install opera 2>&1); then
    echo "ERROR: $SNAP_OUTPUT"
else
    echo "✅ $SNAP_OUTPUT"
fi
DBG_TRACE "2.4"
# MusicBrainz Picard 
if ! SNAP_OUTPUT=$(snap install picard 2>&1); then
    echo "ERROR: $SNAP_OUTPUT"
else
    echo "✅ $SNAP_OUTPUT"
fi
DBG_TRACE "2.5"
# Microsoft PowerShell
if ! SNAP_OUTPUT=$(snap install powershell --classic 2>&1); then
    echo "ERROR: $SNAP_OUTPUT"
else
    echo "✅ $SNAP_OUTPUT"
fi
DBG_TRACE "2.6"
# Mozilla Thunderbird Email Client
if ! SNAP_OUTPUT=$(snap install thunderbird 2>&1); then
    echo "ERROR: $SNAP_OUTPUT"
else
    echo "✅ $SNAP_OUTPUT"
fi
DBG_TRACE "2.7"
# WhatsApp Desktop Client
if ! SNAP_OUTPUT=$(snap install whatsapp-desktop-linux 2>&1); then
    echo "ERROR: $SNAP_OUTPUT"
else
    echo "✅ $SNAP_OUTPUT"
fi
DBG_TRACE "2.8"

# 3. Flatpak Absolute Exceptions
# ------------------------------
echo "Configuring Flatpak..."
# Remove the existing remote to start fresh
flatpak remote-delete flathub 2>/dev/null || true
flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
# Export the paths to the active terminal session
# This bypasses the need to reboot or log out for command-line access
export XDG_DATA_DIRS="/var/lib/flatpak/exports/share:$HOME/.local/share/flatpak/exports/share:$XDG_DATA_DIRS"

# Install Bottles for Wine/Proton compatibility
echo "Installing Bottles for Wine/Proton compatibility..."
flatpak install flathub com.usebottles.bottles -y
DBG_TRACE "3.1"

# Download and install Calibre
echo "Installing Calibre..."
flatpak install flathub com.calibre_ebook.calibre -y
DBG_TRACE "3.2"

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
DBG_TRACE "4.0"

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
DBG_TRACE "4.1"

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
DBG_TRACE "4.2"

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
DBG_TRACE "4.3"

# FreeFileSync Official Setup
echo "Installing FreeFileSync..."
echo "FreeFileSync: Installing required dependencies..."
# Install the correct webkit package for Ubuntu 24.04
apt install -y libgtk-3-0t64 libwebkit2gtk-4.1-0 || echo "ERROR: Failed to install FreeFileSync dependencies."

# Download the official .run installer
FFS_VERSION="14.10" # Check for newer versions on the official website
FFS_URL="https://freefilesync.org/download/FreeFileSync_${FFS_VERSION}_Linux_x86_64.tar.gz"
FFS_TAR_NAME="FreeFileSync_${FFS_VERSION}_Linux_x86_64.tar.gz"
echo "Downloading the FreeFileSync package..."
if wget -q -O "/tmp/$FFS_TAR_NAME" "$FFS_URL"; then
    echo "Extracting /tmp/$FFS_TAR_NAME..."
    tar -xvf "/tmp/$FFS_TAR_NAME" -C /tmp/
    
    # Run the installer
    INSTALLER_PATH="/tmp/FreeFileSync_${FFS_VERSION}_Install.run"
    # Check if the installer exists
    if [ -f "$INSTALLER_PATH" ]; then
        echo "Running the FreeFileSync installer..."
        chmod +x "$INSTALLER_PATH"
        "$INSTALLER_PATH" --accept-license --for-all-users true --create-shortcuts false --skip-overview || echo "ERROR: FreeFileSync installation failed."
    else
        echo "ERROR: Installer script not found at $INSTALLER_PATH"
    fi
    
    # Clean up
    rm -f "/tmp/$FFS_TAR_NAME" "$INSTALLER_PATH"
else
    echo "ERROR: Failed to download $FFS_TAR_NAME"
fi
DBG_TRACE "4.4"

# HandBrake Setup
echo "Installing HandBrake..."
echo "HandBrake: Adding the official PPA..."
# Create the source list file
echo "deb http://ppa.launchpad.net/stebbins/handbrake-releases/ubuntu noble main" | tee /etc/apt/sources.list.d/stebbins-handbrake-releases.list
# Import the PPA's GPG key
apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 43D3C1E1E7B38F3C
# Updating package cache
apt update
apt install -y handbrake || echo "ERROR: Failed to install HandBrake."
DBG_TRACE "4.5"

# Jellyfin Setup 
echo "Installing Jellyfin Media Server..."
echo "Jellyfin: Adding the repository key..."
curl -fsSL https://repo.jellyfin.org/ubuntu/jellyfin_team.gpg.key | gpg --dearmor -o /usr/share/keyrings/jellyfin.gpg

echo "Jellyfin: Adding the repository..."
echo "deb [signed-by=/usr/share/keyrings/jellyfin.gpg] https://repo.jellyfin.org/ubuntu $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/jellyfin.list
# Updating package cache
apt update
apt install -y jellyfin || echo "ERROR: Failed to install Jellyfin."
DBG_TRACE "4.6"

# MEGA Sync Official Setup
echo "Installing MEGA Sync..."
# Download and install the MEGA signing key
curl -fsSL https://mega.nz/keys/MEGA_signing.key | gpg --dearmor -o /etc/apt/keyrings/meganz-archive-keyring.gpg
echo "deb [signed-by=/etc/apt/keyrings/meganz-archive-keyring.gpg] https://mega.nz/linux/repo/xUbuntu_24.04/ ./ " | tee /etc/apt/sources.list.d/megasync.list
# Updating package cache
apt update
apt install -y megasync || echo "ERROR: Failed to install MEGA Sync."
DBG_TRACE "4.7"

# NAPS2 Native APT Repository Setup
echo "Installing NAPS2 Not Another PDF Scanner 2..."
# Download the NAPS2 public key
curl -fsSL https://www.naps2.com/naps2-public.pgp | gpg --dearmor -o /etc/apt/keyrings/naps2.gpg
echo "deb [signed-by=/etc/apt/keyrings/naps2.gpg] https://downloads.naps2.com ./ " | tee /etc/apt/sources.list.d/naps2.list >/dev/null
# Updating package cache
apt update
apt install -y naps2 || echo "ERROR: Failed to install NAPS2."
DBG_TRACE "4.8"
fi # +++++++++++++++++++++++
# OpenClaw AI Assistant Setup
echo "Installing OpenClaw AI Assistant..."
echo "=========================================="
# Uses the official multi-platform setup deployment architecture for OpenClaw
# Install Node.js 22.x+ (required for OpenClaw)
# Remove any existing NodeSource setup to avoid conflicts
echo "Removing existing Node.js packages..."
sudo apt-get purge -y nodejs npm 2>/dev/null || true
sudo apt-get autoremove -y
sudo rm -f /etc/apt/sources.list.d/nodesource.list*
sudo rm -f /etc/apt/sources.list.d/nodesource
curl -fsSL https://deb.nodesource.com/setup_26.x | sudo -E bash -
if [ -f /etc/apt/sources.list.d/nodesource.list ]; then
    echo "✅ NodeSource repository added successfully"
    cat /etc/apt/sources.list.d/nodesource.list
else
    echo "ERROR: NodeSource repository file not found"
    echo "Attempting manual repository addition..."
    
    # Manual fallback if the script fails
    echo "deb [signed-by=/usr/share/keyrings/nodesource.gpg] https://deb.nodesource.com/node_26.x nodistro main" | sudo tee /etc/apt/sources.list.d/nodesource.list
    sudo apt-get update
fi
sudo apt-get update
sudo apt-get install -y nodejs=26.* || {
    echo "ERROR: Failed to install Node.js 26 via apt"
    echo "Trying alternative method..."
    
    # Alternative: Use nvm
    echo "Installing nvm..."
    curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.1/install.sh | bash
    
    export NVM_DIR="$HOME/.nvm"
    [ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"
    
    echo "Installing Node.js 26 via nvm..."
    nvm install 26
    nvm use 26
    nvm alias default 26
}
# Verify the version is correct
if [[ "$NODE_VERSION" == v26* ]]; then
    echo "✅ Node.js $NODE_VERSION installed successfully!"
    echo "npm version: $(npm --version)"
    curl -fsSL https://openclaw.ai/install.sh | bash
else
    echo "ERROR: Node.js $NODE_VERSION is not v26+"
    echo "OpenClaw may not work correctly. Required versions: v22.22.3+, v24.15+, v25.9+"
    echo "ERROR: Node.js and OpenClawinstallation failed."
fi


###curl -fsSL https://deb.nodesource.com/setup_22.x | bash -
###apt install -y nodejs || echo "ERROR: Failed to install Node.js"

# npm is the package manager that is installed automatically as part of Node.js
###echo "Installing OpenClaw by Node.js/npm..."
###npm install -g openclaw@latest || echo "ERROR: Failed to install OpenClaw"
DBG_TRACE "4.9"

# ProtonVPN Official Setup
echo "Installing ProtonVPN..."
# Download the Proton VPN repository package
wget -q -O /tmp/protonvpn-stable-release.deb https://repo.protonvpn.com/debian/dists/stable/main/binary-all/protonvpn-stable-release_1.0.8_all.deb || echo "ERROR: Failed to download ProtonVPN repository package."
if [ -f /tmp/protonvpn-stable-release.deb ]; then
    echo "IMPORTANT: Choose Display Manager for ProtonVPN GUI application: $(cat /etc/X11/default-display-manager)"
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
DBG_TRACE "4.10"

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
DBG_TRACE "4.11"

# RustDesk Remote Desktop Setup
echo "Installing RustDesk..."
# Download the latest RustDesk .deb package from GitHub releases.
# GitHub API responds with JSON data, including a field named "browser_download_url".
PACKAGE_URL=$(curl -s https://api.github.com/repos/rustdesk/rustdesk/releases/latest 2>/dev/null | grep browser_download_url | grep 'bionic_amd64.deb' | cut -d '"' -f 4 | head -1)
# If API failed, use fallback version
if [ -z "$PACKAGE_URL" ]; then
    echo "WARNING: Failed to fetch RustDesk latest version."
    # Using fallback version 1.4.9
    PACKAGE_URL="https://github.com/rustdesk/rustdesk/releases/download/1.4.9/rustdesk-1.4.9-x86_64.deb"
fi
PACKAGE_NAME="/tmp/rustdesk.deb"
# Downloading RustDesk
if wget -q -O "$PACKAGE_NAME" "$PACKAGE_URL"; then
    dpkg -i "$PACKAGE_NAME" || { 
        # Fixing dependencies and retrying"
        apt --fix-broken install -y && dpkg -i "$PACKAGE_NAME"
    } || echo "ERROR: Failed to install RustDesk."
    rm "$PACKAGE_NAME" 2>/dev/null
else
    echo "ERROR: Failed to download RustDesk .deb package."
fi
DBG_TRACE "4.12"

# SMPlayer Setup
echo "Installing SMPlayer..."
# Adding the official PPA for the latest version.
add-apt-repository ppa:alex-p/smplayer -y
# Updating package cache
apt update
apt install -y smplayer smplayer-themes || echo "ERROR: Failed to install SMPlayer."
DBG_TRACE "4.13"

# TailScale zero-config mesh networking setup
echo "Installing Tailscale..."
# Add Tailscale's package signing key and repository
curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/noble.noarmor.gpg | sudo tee /usr/share/keyrings/tailscale-archive-keyring.gpg >/dev/null
curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/noble.tailscale-keyring.list | sudo tee /etc/apt/sources.list.d/tailscale.list
apt update
apt install -y tailscale || echo "ERROR: Failed to install Tailscale."
DBG_TRACE "4.14"

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
DBG_TRACE "4.15"

# ZeroTier zero-config mesh networking setup
echo "Installing ZeroTier..."
# Install ZeroTier using the official one-line installer
curl -s https://install.zerotier.com | bash
# Check if installation was successful
if ! command -v zerotier-cli &> /dev/null; then
    echo "ERROR: ZeroTier installation failed."
fi
DBG_TRACE "4.16"

# 5. Standalone Portable Setup (AppImage)
echo "Setting up Portable Applications Directory..."
mkdir -p /opt/AppImages
DBG_TRACE "5.0"

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
echo "NOTE: Please log out and back in (or reboot) for Flatpak applications to appear in your menu."
