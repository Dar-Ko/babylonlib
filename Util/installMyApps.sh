#!/bin/bash

# Ensure the script runs with root privileges
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script using sudo: sudo ./installMyApps.sh"
  exit 1
fi

echo "=========================================="
echo " Starting Expanded Application Sync"
echo "=========================================="

# 1. Add Third-Party APT Repositories First

mkdir -p /etc/apt/keyrings
# NAPS2 Native APT Repository Setup
echo "Adding NAPS2 Official APT Repository..."
curl -fsSL https://naps2.com -o /etc/apt/keyrings/naps2.asc 2>/dev/null
echo "deb [signed-by=/etc/apt/keyrings/naps2.asc] https://naps2.com ./" | tee /etc/apt/sources.list.d/naps2.list >/dev/null

# MEGA Sync Official Setup
echo "Configuring MEGA Sync Repository..."
curl -fsSL https://mega.nz | gpg --dearmor | tee /etc/apt/keyrings/meganz-archive-keyring.gpg > /dev/null
echo "Types: deb
URIs: https://mega.nz
Suites: ./
Signed-By: /etc/apt/keyrings/meganz-archive-keyring.gpg" | tee /etc/apt/sources.list.d/megaio.sources > /dev/null

# ProtonVPN Official Setup
echo "Configuring ProtonVPN..."
wget -qN https://protonvpn.com -O /tmp/protonvpn.deb
dpkg -i /tmp/protonvpn.deb

# Refresh packages with new repositories active
apt update && apt upgrade -y

# 2. Crash-Proof Native APT Loop
# If one package fails or changes upstream, the script will skip it and finish the rest.
apt_apps=(
    "dconf-editor" "asunder" "picard" "sayonara" "pavucontrol" 
    "meld" "caja-actions" "pdfarranger" "thunderbird" "remmina" 
    "gthumb" "keepassxc" "remaster-iso" "git" "curl" "wget" "flatpak"
    "naps2" "krop" "duplicity" "7zip" "stacer" "xchm" "qbittorrent" "vlc"
)

echo "Installing native APT packages one-by-one..."
for app in "${apt_apps[@]}"; do
    echo "Installing: $app..."
    apt install -y "$app" || echo "WARNING: Failed to install $app, skipping..."
done

# 3. Snap Store Configurations
echo "Installing Snap applications..."
snap install powershell --classic
snap install code --classic
snap install joplin-desktop

# 4. Official Automated Scripts (Tailscale, ZeroTier, Jellyfin, OpenClaw)
echo "Installing Tailscale..."
curl -fsSL https://tailscale.com | sh

echo "Installing ZeroTier..."
curl -s https://zerotier.com | bash

echo "Installing Jellyfin Server..."
curl -fsSL https://jellyfin.org | bash

echo "Deploying OpenClaw AI Assistant..."
# Uses the official multi-platform setup deployment architecture for OpenClaw
curl -fsSL https://openclaw.ai/install.sh | bash

# 5. External .deb Manual Pulls (RustDesk & AppImageLauncher)
echo "Downloading and deploying RustDesk..."
wget -q https://github.com -O /tmp/rustdesk.deb
dpkg -i /tmp/rustdesk.deb || apt-get install -f -y

echo "Downloading and deploying AppImageLauncher..."
# Uses the Ubuntu 24.04 compatible continuous-release pipeline asset
wget -q https://github.com -O /tmp/appimages.deb
dpkg -i /tmp/appimages.deb || apt-get install -f -y

# 6. Standalone Portable Setup (FreeFileSync & GIMP AppImage)
echo "Setting up Portable Applications Directory..."
mkdir -p /opt/AppImages

# Download GIMP AppImage directly to system location
wget -q https://github.com -O /opt/AppImages/GIMP.AppImage
chmod +x /opt/AppImages/GIMP.AppImage

# 7. Flatpak Absolute Exceptions (Bottles Only)
echo "Configuring Flatpak strictly for Bottles..."
flatpak remote-add --if-not-exists flathub https://flathub.org
flatpak install -y flathub com.usebottles.bottles

echo "=========================================="
echo " Installation process finished! "
echo "=========================================="
echo "Manual tasks left:"
echo "1. FreeFileSync: Extract its official Linux tarball directly into your home folder."
echo "2. OpenClaw: Run 'openclaw' in the terminal to initialize config variables and sync asset folders."

