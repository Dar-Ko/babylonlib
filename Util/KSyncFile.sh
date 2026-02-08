#!/bin/bash
########################################
# Automatically syncs newer file in either direction, based on modification
# UTC timestamps.
# Creates only one backup copy of the previous file version.
# Missing files are handled gracefully.
# User interaction, such as password prompts and host key confirmation requests,
# is disabled.
#
# Setup:
#   chmod +x KSyncFile.sh
# Configure SSH Key Authentication to avoid password prompts
#   ssh-keygen -t rsa
#   ssh-copy-id -i ~/.ssh/id_rsa.pub "$REMOTE_USER@$REMOTE_HOST"
# For periodic execution and boot-time run, set Cron jobs:
#   crontab -e
# Add next lines to the crontab
#   @reboot (date; /path/to/KSyncFile.sh) >/tmp/KSyncFile.log 2>&1
#   0 */12 * * * (date; /path/to/KSyncFile.sh) >>/tmp/KSyncFile.log 2>&1

# Uncomment next line to allow debugging
#set -xv

# Configuration
 LOCAL_FILE="/path/to/local/file"         # Local file path
 REMOTE_USER="username"                   # Remote server username
 REMOTE_HOST="remote.example.com"         # Remote server hostname/IP
 REMOTE_DIR="/path/to/remote/directory"   # Remote directory path
 BACKUP_SUFFIX=".bak"                     # Backup file suffix

# Get filename from path
FILE_NAME=$(basename "$LOCAL_FILE")
REMOTE_FILE="$REMOTE_DIR/$FILE_NAME"

# To allow background process with own shell and own environment variables (like
# cron has) to run this script, the correct SSH environment variable is required.
# To get the proper value of the SSH_AUTH_SOCK, run command:
#   env|grep -i ssh
# and replace the export line bellow with the result.
# Note: in the case that keys are managed by ssh-agent, the result will be
# a temporary key: SSH_AUTH_SOCK=/tmp/ssh-.../agent...
# the following lines are also required:
#   tmp_auth=`find /tmp -user $LOGNAME -type s -name "*agent*" -print 2>/dev/null`
#   SSH_AUTH_SOCK=$auth
#   export SSH_AUTH_SOCK
# ssh -a option disables forwarding of the authentication agent connection.
if [ -z "$SSH_AUTH_SOCK" ]; then
    export SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
fi

########################################
# Function to get UTC timestamp of a file (0 if file doesn't exist)
get_utc_timestamp() {
    if [ -e "$1" ]; then
        stat -c %Y "$1"
    else
        echo 0
    fi
}

########################################
# Function to create backup
create_backup() {
    local file_path="$1"
    if [ -e "$file_path" ]; then
        # Remove previous backup if exists
        rm -f "${file_path}${BACKUP_SUFFIX}"
        # Create new backup
        mv "$file_path" "${file_path}${BACKUP_SUFFIX}"
        echo "Created backup: ${file_path}${BACKUP_SUFFIX}"
    fi
}

########################################
# Verify accessibility of the remote file
# Example usage
#  check_ssh_access "user@example.com" "/path/to/file"
check_ssh_access() {
    local remote_host="$1"
    local remote_file="$2"
    
    # Attempt SSH command and capture all outputs
    local error_output
    error_output=$(ssh -axo BatchMode=yes "$remote_host" "test -r \"$remote_file\" && echo 'OK'" 2>&1)
    local exit_code=$?

    if [[ $exit_code -eq 0 ]]; then
        if [[ "$error_output" == *OK* ]]; then
            # Access Granted, return OK
            return 0
        fi
    else
        # Parse different error types
        case "$error_output" in
            *"Permission denied"*"publickey"*)
                echo "SSH Authentication Failed $exit_code:: ${error_output//$'\r'/}"
                ;;
            *"Permission denied"*)
                echo "File Access Denied $exit_code:: ${error_output//$'\r'/}"
                ;;
            *"No such file or directory"*)
                echo "File Not Found $exit_code:: ${error_output//$'\r'/}"
                ;;
            *"Connection refused"*)
                echo "Network Error $exit_code:: ${error_output//$'\r'/}"
                ;;
            *"Could not resolve hostname"*)
                echo "DNS Error $exit_code:: ${error_output//$'\r'/}"
                ;;
            *)
                echo "Unknown Error $exit_code:: ${error_output//$'\r'/}"
                ;;
        esac
        # Return ERROR
        return 1
    fi
}


# Check the remote file
check_ssh_access "$REMOTE_USER@$REMOTE_HOST" "$REMOTE_FILE"
error=$?
echo "Returned " $error
if [[ $error -eq 0 ]]; then
    # Get timestamps
    LOCAL_TS=$(get_utc_timestamp "$LOCAL_FILE")
    REMOTE_TS=$(ssh -axo BatchMode=yes "$REMOTE_USER@$REMOTE_HOST" "stat -c %Y '$REMOTE_FILE' 2>/dev/null || echo 0")

    # Synchronization logic
    if [ "$LOCAL_TS" -gt "$REMOTE_TS" ]; then
        echo "Local file is newer (UTC)"
        # Backup and copy to remote
        ssh "$REMOTE_USER@$REMOTE_HOST" "rm -f '${REMOTE_FILE}${BACKUP_SUFFIX}'; \
            [ -e '$REMOTE_FILE' ] && mv '$REMOTE_FILE' '${REMOTE_FILE}${BACKUP_SUFFIX}'"
        rsync -avz -e ssh "$LOCAL_FILE" "$REMOTE_USER@$REMOTE_HOST:$REMOTE_FILE"
    elif [ "$REMOTE_TS" -gt "$LOCAL_TS" ]; then
        echo "Remote file is newer (UTC)"
        # Backup and copy to local
        create_backup "$LOCAL_FILE"
        rsync -avz -e ssh "$REMOTE_USER@$REMOTE_HOST:$REMOTE_FILE" "$LOCAL_FILE"
    else
        echo "Files are synchronized (UTC)"
    fi
fi
