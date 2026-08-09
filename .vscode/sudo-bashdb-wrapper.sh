#!/bin/bash
# This wrapper runs the bashdb bundled with the vscode-bash-debug extension with sudo

# Dynamically find the bashdb path at runtime
BASHDB_PATH=$(find ~/.vscode/extensions/ -name "bashdb" -path "*/bashdb_dir/*" 2>/dev/null | head -1)

if [ -z "$BASHDB_PATH" ]; then
    echo "ERROR: Could not find bashdb in VS Code extensions directory."
    exit 1
fi

sudo "$BASHDB_PATH" "$@"
