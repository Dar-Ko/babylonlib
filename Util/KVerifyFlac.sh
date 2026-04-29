#!/bin/bash
#
# .SYNOPSIS
# Verify integrity of FLAC audio files in a directory
# .USAGE
#  ./KVerifyFlac.sh [directory]
#  If directory is omitted, current directory is used.
# .DESCRIPTION
# The script recursively finds all .flac files (case-insensitive) and runs
# 'flac -wt' (test/decode mode) on each. Any errors are written to
# flac-errors.txt inside the target directory. A summary is printed to stdout.

set -euo pipefail

# Check for required 'flac' command
if ! command -v flac &> /dev/null; then
    echo "ERROR: 'flac' command not found. Please install FLAC tools."
    exit 1
fi

# Determine target directory (argument or current dir)
TARGET_DIR="${1:-.}"
if [ ! -d "$TARGET_DIR" ]; then
    echo "ERROR: Directory '$TARGET_DIR' does not exist."
    exit 2
fi

# Path to the error log inside the target directory
ERROR_LOG="$TARGET_DIR/flac-errors.txt"

# Clear or create new error log
> "$ERROR_LOG"

total_files=0
error_files=0

echo "Verifying FLAC audio files on '$TARGET_DIR'"
# Use find with -print0 to handle filenames with spaces or special characters
while IFS= read -r -d '' flac_file; do
    ((++total_files))
    echo -n "Checking: $flac_file ... "

    # Run flac -t, capture stderr (errors) while discarding stdout
    # The exit status tells us if the file is valid.
    if err_output=$(flac -t "$flac_file" 2>&1 >/dev/null); then
        echo "OK"
    else
        echo "ERROR"
        ((++error_files))

        # Write details to the error log
        echo "===== $flac_file =====" >> "$ERROR_LOG"
        echo "$err_output" >> "$ERROR_LOG"
        echo "" >> "$ERROR_LOG"   # blank line separator
    fi
done < <(find "$TARGET_DIR" -type f -iname "*.flac" -print0)

# Print summary
echo "--------------------------------"
echo "Total FLAC files found: $total_files"
echo "Files with errors:      $error_files"

if [ $error_files -eq 0 ]; then
    echo "All FLAC files are valid."
    # Remove the empty error log (optional)
    rm -f "$ERROR_LOG"
else
    echo "-------------------------------------------------" >> "$ERROR_LOG"
    echo "Total FLAC files found: $total_files" >> "$ERROR_LOG"
    echo "Files with errors:      $error_files" >> "$ERROR_LOG"

    echo "See '$ERROR_LOG' for error details."
fi

# Exit with non-zero status if any errors were found
[ $error_files -eq 0 ] && exit 0 || exit 3
