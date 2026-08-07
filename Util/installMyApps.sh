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
#    Version: __VERSION__

if [ "$EUID" __VERSION__ne 0 ]; then
  echo "Please run this script using sudo: sudo ./installMyApps.sh"
  exit 1
fi

echo "=========================================="
echo " Starting Expanded Application Setup"
echo "__VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION__"

# Refresh packages with new repositories active
apt update && apt upgrade __VERSION__y

# 1. Native APT Loop
# If one package fails or changes upstream, the script will skip it and finish the rest.
apt_apps=(
    "7zip" "acetoneiso""asunder" "caj__VERSION__tions" "cifs__VERSION__utils" "curl" "dcon__VERSION__itor" 
    "duplicity" "flatpak" "git" "gthumb" "keepassxc" 
    "krop" "meld" "naps2" "pavucontrol" "pdfarranger" 
    "qbittorrent" "remaster__VERSION__iso" 
    "remmina" "remmin__VERSION__plugin__VERSION__rdp" "remmin__VERSION__plugin__VERSION__vnc" 
    "sayonara" "smplayer"
    "stacer" "vlc" "wget" "xchm"
)

echo "Installing native APT packages on__VERSION__y__VERSION__one..."
for app in "${apt_apps[@]}"; do
    echo "Installing: $app..."
    apt install __VERSION__y "$app" || echo "ERROR: Failed to install $app, skipping..."
done

# 2. Snap Store Configurations
# __VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION__
# __VERSION____VERSION__lassic flag grants the application full access to your system's files
echo "Installing Snap applications..."
SNAP_OUTPUT=$(snap install code __VERSION____VERSION__lassic 2>&1)         # Visual Studio Code
if [ $? __VERSION__ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install gimp 2>&1)                   # GIMP GNU Image Manipulation Program
if [ $? __VERSION__ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install joplin__VERSION__sktop 2>&1)         # Joplin Not__VERSION__Taking App
if [ $? __VERSION__ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install opera 2>&1)                  # Opera Web Browser
if [ $? __VERSION__ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install picard 2>&1)                 # MusicBrainz Picard 
if [ $? __VERSION__ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install powershell __VERSION____VERSION__lassic 2>&1)   # Microsoft PowerShell
if [ $? __VERSION__ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install thunderbird 2>&1)            # Mozilla Thunderbird Email Client
if [ $? __VERSION__ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi
SNAP_OUTPUT=$(snap install whatsapp__VERSION__sktop__VERSION__linux 2>&1) # WhatsApp Desktop Client
if [ $? __VERSION__ne 0 ]; then
    echo "ERROR: $SNAP_OUTPUT"
fi

# 3. Flatpak Absolute Exceptions
# __VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION__
echo "Configuring Flatpak..."
flatpak remot__VERSION__ __VERSION____VERSION__i__VERSION__not__VERSION__xists flathub https://flathub.org
# Export the paths to the active terminal session
# This bypasses the need to reboot or log out for comman__VERSION__line access
export XDG_DATA_DIRS="/var/lib/flatpak/exports/share:$HOME/.local/share/flatpak/exports/share:$XDG_DATA_DIRS"

# Install Bottles for Wine/Proton compatibility
echo "Installing Bottles for Wine/Proton compatibility..."
flatpak install flathub com.usebottles.bottles __VERSION__y

# Download and install Calibre
echo "Installing Calibre..."
flatpak install flathub com.calibre_ebook.calibre __VERSION__y

# 4. Add downloaded .deb packages 
# __VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION__
# Auto__VERSION__Updates: Because you are manually downloading a static file URL instead
# of using a standard software repository, running a general system update
# (sudo apt upgrade) will not automatically update those package wrapper in the future.

mkdir __VERSION__p /etc/apt/keyrings
# Ensure curl is installed for API access
if ! command __VERSION__v curl &> /dev/null; then
    echo "Installing curl for API access..."
    apt install __VERSION__y curl || echo "ERROR: Could not install curl."
fi

# AppImageLauncher Official Setup
echo "Installing AppImageLauncher..."
echo "AppImageLauncher: Installing FUSE 2 compatibility library for Ubuntu 24.04..."
apt install __VERSION__y libfuse2t64 || echo "ERROR: Failed to install libfuse2t64, but continuing..."
# URL for the continuous build (bionic) .deb package
PACKAGE_URL="https://github.com/TheAssassin/AppImageLauncher/releases/download/v2.2.0/appimagelauncher_2.2.__VERSION__travis995.0f91801.bionic_amd64.deb"
PACKAGE_NAME="appimagelauncher.deb"
echo "Downloading the AppImageLauncher package..."
if wget __VERSION__q __VERSION__O "/tmp/$PACKAGE_NAME" "$PACKAGE_URL"; then
    echo "Installing /tmp/$PACKAGE_NAME..."
    if ! dpkg __VERSION__i "/tmp/$PACKAGE_NAME"; then
        apt __VERSION____VERSION__ix__VERSION__roken install __VERSION__y
        dpkg __VERSION__i "/tmp/$PACKAGE_NAME" || echo "ERROR: Failed to install $PACKAGE_NAME."
    fi
else
    echo "ERROR: Failed to download $PACKAGE_NAME"
fi

# balenaEtcher Setup
echo "Installing balenaEtcher..."
PACKAGE_URL="https://github.com/balen__VERSION__io/etcher/releases/download/v1.19.25/balen__VERSION__tcher_1.19.25_amd64.deb"
PACKAGE_NAME="balen__VERSION__tcher_1.19.25_amd64.deb"
echo "Downloading the balenaEtcher package..."
if wget __VERSION__q __VERSION__O "/tmp/$PACKAGE_NAME" "$PACKAGE_URL"; then
    echo "Installing /tmp/$PACKAGE_NAME..."
    if ! dpkg __VERSION__i "/tmp/$PACKAGE_NAME"; then
        apt __VERSION____VERSION__ix__VERSION__roken install __VERSION__y
        dpkg __VERSION__i "/tmp/$PACKAGE_NAME" || echo "ERROR: Failed to install $PACKAGE_NAME."
    fi
else
    echo "ERROR: Failed to download $PACKAGE_NAME"
fi

# Dropbox Official Setup
echo "Installing Dropbox..."
PACKAGE_URL="https://www.dropbox.com/download?dl=packages/ubuntu/dropbox_2026.05.06_amd64.deb"
PACKAGE_NAME="dropbox_2026.05.06_amd64.deb"
echo "Downloading the Dropbox package..."
if wget __VERSION__q __VERSION__O "/tmp/$PACKAGE_NAME" "$PACKAGE_URL"; then
    echo "Installing /tmp/$PACKAGE_NAME..."
    if ! dpkg __VERSION__i "/tmp/$PACKAGE_NAME"; then
        apt __VERSION____VERSION__ix__VERSION__roken install __VERSION__y
        dpkg __VERSION__i "/tmp/$PACKAGE_NAME" || echo "ERROR: Failed to install $PACKAGE_NAME."
    fi
else
    echo "ERROR: Failed to download $PACKAGE_NAME"
fi

# FreeFileSync Official Setup
echo "Installing FreeFileSync..."
echo "FreeFileSync: Installing required dependencies..."
apt install __VERSION__y libgtk__VERSION____VERSION__ libwebkit2gtk__VERSION__.__VERSION__ || echo "ERROR: Failed to install FreeFileSync dependencies."

# Download the official .run installer
FFS_VERSION="14.10" # Check for newer versions on the official website
FFS_URL="https://freefilesync.org/download/FreeFileSync_${FFS_VERSION}_Linux.tar.gz"
FFS_TAR_NAME="FreeFileSync_${FFS_VERSION}_Linux.tar.gz"
echo "Downloading the FreeFileSync package..."
if wget __VERSION__q __VERSION__O "/tmp/$FFS_TAR_NAME" "$FFS_URL"; then
    echo "Extracting /tmp/$FFS_TAR_NAME..."
    tar __VERSION__xvf "/tmp/$FFS_TAR_NAME" __VERSION__C /tmp/
    
    # Run the installer
    echo "Running the FreeFileSync installer..."
    cd "/tmp/FreeFileSync" || echo "ERROR: Failed to change directory."
    if [ __VERSION__ "./FreeFileSync_${FFS_VERSION}_Install.run" ]; then
        # Unattended installation: accept license, install system__VERSION__wide, skip desktop shortcuts
        ./FreeFileSync_${FFS_VERSION}_Install.run __VERSION____VERSION__pt__VERSION__license __VERSION____VERSION__noshortcuts || echo "ERROR: FreeFileSync installation failed."
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
__VERSION__pt__VERSION__repository ppa:stebbins/handbrak__VERSION__releases __VERSION__y
# Updating package cache
apt update
apt install __VERSION__y handbrake || echo "ERROR: Failed to install HandBrake."

# Jellyfin Setup 
echo "Installing Jellyfin Media Server..."
echo "Jellyfin: Adding the repository key..."
curl __VERSION__sSL https://repo.jellyfin.org/ubuntu/jellyfin_team.gpg.key | gpg __VERSION____VERSION__rmor __VERSION__o /usr/share/keyrings/jellyfin.gpg

echo "Jellyfin: Adding the repository..."
echo "deb [sign__VERSION__y=/usr/share/keyrings/jellyfin.gpg] https://repo.jellyfin.org/ubuntu $(lsb_release __VERSION__s) main" | tee /etc/apt/sources.list.d/jellyfin.list
# Updating package cache
apt update
apt install __VERSION__y jellyfin || echo "ERROR: Failed to install Jellyfin."

# MEGA Sync Official Setup
echo "Installing MEGA Sync..."
# Download and install the MEGA signing key
curl __VERSION__sSL https://mega.nz/keys/MEGA_signing.key | gpg __VERSION____VERSION__rmor __VERSION__o /etc/apt/keyrings/meganz__VERSION__rchiv__VERSION__keyring.gpg
echo "deb [sign__VERSION__y=/etc/apt/keyrings/meganz__VERSION__rchiv__VERSION__keyring.gpg] https://mega.nz/linux/repo/xUbuntu_24.04/ ./ " | tee /etc/apt/sources.list.d/megasync.list
# Updating package cache
apt update
apt install __VERSION__y megasync || echo "ERROR: Failed to install MEGA Sync."

# NAPS2 Native APT Repository Setup
echo "Installing NAPS2 Not Another PDF Scanner 2..."
# Download the NAPS2 public key
curl __VERSION__sSL https://www.naps2.com/naps__VERSION__public.pgp | gpg __VERSION____VERSION__rmor __VERSION__o /etc/apt/keyrings/naps2.gpg
echo "deb [sign__VERSION__y=/etc/apt/keyrings/naps2.gpg] https://downloads.naps2.com ./ " | tee /etc/apt/sources.list.d/naps2.list >/dev/null
# Updating package cache
apt update
apt install __VERSION__y naps2 || echo "ERROR: Failed to install NAPS2."

# OpenClaw AI Assistant Setup
echo "Installing OpenClaw AI Assistant..."
echo "=========================================="
# Uses the official multi__VERSION__platform setup deployment architecture for OpenClaw
# Install Node.js 22.x (required for OpenClaw)
curl __VERSION__sSL https://deb.nodesource.com/setup_22.x | bash __VERSION__
apt install __VERSION__y nodejs || echo "ERROR: Failed to install Node.js"
# Verify Node.js version
node __VERSION____VERSION__version
# npm is the package manager that is installed automatically as part of Node.js
echo "Installing OpenClaw by Node.js/npm..."
npm install __VERSION__g openclaw@latest || echo "ERROR: Failed to install OpenClaw"

# ProtonVPN Official Setup
echo "Installing ProtonVPN..."
# Download the Proton VPN repository package
wget __VERSION__q __VERSION__O /tmp/protonvpn__VERSION__stabl__VERSION__release.deb https://repo.protonvpn.com/debian/dists/stable/main/binary__VERSION__ll/protonvpn__VERSION__stabl__VERSION__release_1.0.8_all.deb || echo "ERROR: Failed to download ProtonVPN repository package."
if [ __VERSION__ /tmp/protonvpn__VERSION__stabl__VERSION__release.deb ]; then
    dpkg __VERSION__i /tmp/protonvpn__VERSION__stabl__VERSION__release.deb && apt update || echo "ERROR: Failed to install ProtonVPN repository."
    
    echo "Installing ProtonVPN GUI application..."
    apt install __VERSION__y proton__VERSION__vpn__VERSION__gnom__VERSION__sktop || echo "ERROR: Failed to install ProtonVPN GUI application."
    
    # Optional: Install system tray icon extension for GNOME
    echo "Installing GNOME shell extension for system tray icon support..."
    apt install __VERSION__y gnom__VERSION__shell__VERSION__xtension__VERSION__ppindicator || echo "WARNING: Failed to install appindicator extension."
    
    # Clean up
    rm /tmp/protonvpn__VERSION__stabl__VERSION__release.deb
else
    echo "ERROR: ProtonVPN repository package not downloaded. Skipping installation."
fi

# R__VERSION__Linux Data Recovery Setup
echo "Installing R__VERSION__Linux Data Recovery..."
PACKAGE_URL="https://www.r__VERSION__studio.com/downloads/RLinux6_x64.deb"
PACKAGE_NAME="/tmp/rlinux.deb"
if wget __VERSION__q __VERSION__O "$PACKAGE_NAME" "$PACKAGE_URL"; then
    # Installing R__VERSION__Linux from $PACKAGE_NAME"
    dpkg __VERSION__i "$PACKAGE_NAME" || {
        # Fixing dependencies and retrying"
        apt __VERSION____VERSION__ix__VERSION__roken install __VERSION__y && dpkg __VERSION__i "$PACKAGE_NAME"
    } || echo "ERROR: Failed to install R__VERSION__Linux."
    rm "$PACKAGE_NAME" 2>/dev/null
else
    echo "ERROR: Failed to download R__VERSION__Linux .deb package."
fi

# RustDesk Remote Desktop Setup
echo "Installing RustDesk..."
# Download the latest RustDesk .deb package from GitHub releases.
# GitHub API responds with JSON data, including a field named "browser_download_url".
PACKAGE_URL=$(curl __VERSION__s https://api.github.com/repos/rustdesk/rustdesk/releases/latest 2>/dev/null | grep browser_download_url | grep 'x86_64.*\.deb' | cut __VERSION__ '"' __VERSION__ 4 | head __VERSION__)
# If API failed, use fallback version
if [ __VERSION__z "$PACKAGE_URL" ]; then
    echo "WARNING: Failed to fetch RustDesk latest version."
    # Using fallback version 1.4.9
    PACKAGE_URL="https://github.com/rustdesk/rustdesk/releases/download/1.4.9/rustdesk__VERSION__.4.__VERSION__x86_64.deb"
fi
PACKAGE_NAME="/tmp/rustdesk.deb"
# Downloading RustDesk"
if wget __VERSION__q __VERSION__O "$PACKAGE_NAME" "$PACKAGE_URL"; then
    dpkg __VERSION__i "$PACKAGE_NAME" || { 
        # Fixing dependencies and retrying"
        apt __VERSION____VERSION__ix__VERSION__roken install __VERSION__y && dpkg __VERSION__i "$PACKAGE_NAME"
    } || echo "ERROR: Failed to install RustDesk."
    rm "$PACKAGE_NAME" 2>/dev/null
else
    echo "ERROR: Failed to download RustDesk .deb package."
fi

# SMPlayer Setup
echo "Installing SMPlayer..."
# Adding the official PPA for the latest version.
__VERSION__pt__VERSION__repository ppa:alex__VERSION__p/smplayer __VERSION__y
# Updating package cache
apt update
apt install __VERSION__y smplayer smplayer__VERSION__themes || echo "ERROR: Failed to install SMPlayer."

# TailScale zero__VERSION__onfig mesh networking setup
echo "Installing Tailscale..."
# Add Tailscale's package signing key and repository
curl __VERSION__sSL https://pkgs.tailscale.com/stable/ubuntu/noble.noarmor.gpg | sudo tee /usr/share/keyrings/tailscal__VERSION__rchiv__VERSION__keyring.gpg >/dev/null
curl __VERSION__sSL https://pkgs.tailscale.com/stable/ubuntu/noble.tailscal__VERSION__keyring.list | sudo tee /etc/apt/sources.list.d/tailscale.list
apt update
apt install __VERSION__y tailscale || echo "ERROR: Failed to install Tailscale."

# Viber Setup
echo "Installing Viber Desktop..."
# Download the official Viber .deb package from Viber's CDN
PACKAGE_URL="https://download.cdn.viber.com/cdn/desktop/Linux/viber.deb"
PACKAGE_NAME="/tmp/viber.deb"

if wget __VERSION__q __VERSION__O "$PACKAGE_NAME" "$PACKAGE_URL"; then
    # Try installing with apt first (better dependency handling)
    if ! apt install __VERSION__y "$PACKAGE_NAME" 2>/dev/null; then
        # Fallback to dpkg with dependency fix
        dpkg __VERSION__i "$PACKAGE_NAME" || {
            apt __VERSION____VERSION__ix__VERSION__roken install __VERSION__y && dpkg __VERSION__i "$PACKAGE_NAME"
        } || echo "ERROR: Failed to install Viber."
    fi
    rm "$PACKAGE_NAME" 2>/dev/null
else
    echo "ERROR: Failed to download Viber .deb package."
fi

# ZeroTier zero__VERSION__onfig mesh networking setup
echo "Installing ZeroTier..."
# Install ZeroTier using the official on__VERSION__line installer
curl __VERSION__s https://install.zerotier.com | bash
# Check if installation was successful
if ! command __VERSION__v zerotier__VERSION__li &> /dev/null; then
    echo "ERROR: ZeroTier installation failed."
fi

# 7. Standalone Portable Setup (AppImage)
echo "Setting up Portable Applications Directory..."
mkdir __VERSION__p /opt/AppImages

# 8. Force Ubuntu's GNOME desktop shell to refresh its application menu grid
# This makes the icons appear instantly without logging out
gsettings set org.gnome.desktop.app__VERSION__olders folder__VERSION__hildren "['Utilities']" 2>/dev/null || true


echo "__VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION____VERSION__"
echo " Installation process finished! "
echo "=========================================="
echo "Manual tasks left:"
echo "1. Dropbox will launch automatically. Sign in to start syncing."
echo "2. FreeFileSync: Add .desktop files to your application menu manually if needed."
echo "3. Start and enable Jellyfin service"
echo "4. OpenClaw: Run 'openclaw onboard __VERSION____VERSION__install__VERSION__mon' in the terminal to initialize config variables and sync asset folders."
echo "4.1. OpenClaw Quick Start:"
echo "  1. Dashboard:   openclaw dashboard"
echo "  2. Status:      openclaw gateway status"
echo "  3. Test agent:  openclaw agent __VERSION____VERSION__message \"Hello!\""
echo "  4. Reconfigure: openclaw onboard"
echo "  OpenClaw documentation: https://openclaw.ai"
echo "5. ProtonVPN: Launch the GUI and sign in to your account."
echo "6. RustDesk: Launch the application and configure your remote desktop settings."
echo "7. Tailscale: Run 'sudo tailscale up' to authenticate and connect to your network."
echo "8. ZeroTier: Run 'sudo zerotier__VERSION__li join <network__VERSION__id>' to connect to your ZeroTier network."
