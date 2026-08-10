#!/bin/bash
# This wrapper runs the bashdb bundled with the vscode-bash-debug extension with sudo

# Dynamically find the bashdb path at runtime
BASHDB_PATH=$(find ~/.vscode/extensions/ -name "bashdb" -path "*/bashdb_dir/*" 2>/dev/null | head -1)

if [ -z "$BASHDB_PATH" ]; then
    echo "ERROR: Could not find bashdb in VS Code extensions directory."
    exit 1
fi

# Since the Bash Debug (rogalmic) extension hardcodes /tmp, we need to make
# the FIFO writable by root when sudo runs.

# Bash Debug (rogalmic) will try to create FIFO at /tmp/vscode-bash-debug-fifo-*
# We need to ensure root can write to it.
# Kill any leftover FIFO first
rm -f /tmp/vscode-bash-debug-fifo-* 2>/dev/null

# Try 1: Run bashdb with sudo, but this may fail due to FIFO permissions
#sudo "$BASHDB_PATH" "$@"

# Try 2: Run bashdb with sudo and set umask to allow FIFO creation
# Create a script that runs as root but sets umask for FIFO
sudo bash -c "umask 0000; sudo $BASHDB_PATH $*"

# Try 3: Use script to create a pseudo-terminal for sudo, but this may not work in all environments
# Fixing issue is often that the debugged process doesn't have access to a real
# terminal (TTY) needed for interactive password entry
# Use the `script` command to create a pseudo-terminal
## script -q -c "sudo '$BASHDB_PATH' '$@'" /dev/null

# Try 4: Use a wrapper script to run bashdb with sudo and set permissions on the FIFO
# Run the debugger in the background and change permissions
# This is a hack: start bashdb, wait for FIFO creation, then chmod it
#(
#    # Start bashdb in background
#    "$BASHDB_PATH" "$@" &
#    PID=$!
#    
#    # Wait a moment for FIFO to be created
#    sleep 0.5
#    
#    # Make all FIFOs world-writable
#    chmod 666 /tmp/vscode-bash-debug-fifo-* 2>/dev/null
#    
   # Wait for debugger to finish
#   wait $PID
#)


