#!/bin/bash

# Script to collect all files matching pattern _NNIndex.tsv from subdirectories
# and copy them to a temporary folder preserving directory structure
# chmod +x KCollectIndexFiles.sh
# ./KCollectIndexFiles.sh /path/to/source
#
# - Searches recursively for files matching the pattern *_NNIndex.tsv where NN is a number
# - Creates a temporary directory in /tmp/ with a timestamp to avoid conflicts
# - Preserves directory structure when copying files
# - Shows progress as files are copied
# - Provides a summary at the end with total count and location


# Set the source directory (current directory by default)
SOURCE_DIR="${1:-.}"

# Validate source directory exists
if [ ! -d "$SOURCE_DIR" ]; then
    echo "Error: Source directory '$SOURCE_DIR' does not exist!" >&2
    exit 1
fi

# Create temporary directory with timestamp
TEMP_DIR="/tmp/collected_files_$(date +%Y%m%d_%H%M%S)"
if ! mkdir -p "$TEMP_DIR"; then
    echo "Error: Failed to create temporary directory '$TEMP_DIR'" >&2
    exit 1
fi

echo "=========================================="
echo "File Collection Script"
echo "=========================================="
echo "Source directory: $(realpath "$SOURCE_DIR")"
echo "Temporary directory: $TEMP_DIR"
echo "File pattern: *_NNIndex.tsv (where NN is a number)"
echo "=========================================="
echo ""

# Use a counter to track files
file_count=0

# Process files
find "$SOURCE_DIR" -type f -name '*_[0-9][0-9]Index.tsv' -print0 | while IFS= read -r -d '' file; do
    # Get the relative path from source directory
    rel_path="${file#$SOURCE_DIR/}"
    # Handle case where SOURCE_DIR is current directory
    if [[ "$SOURCE_DIR" == "." && "$rel_path" == "$file" ]]; then
        rel_path="${file#./}"
    fi
    
    # Create the target directory structure
    target_dir="$TEMP_DIR/$(dirname "$rel_path")"
    mkdir -p "$target_dir"
    
    # Copy the file
    if cp -p "$file" "$target_dir/"; then
        ((file_count++))
        echo "[$file_count] ✓ $(basename "$file") -> $(dirname "$rel_path")/"
    else
        echo "[ERROR] Failed to copy: $file" >&2
    fi
done < <(find "$SOURCE_DIR" -type f -regex '.*_[0-9]+Index\.tsv' -print0)

echo ""
echo "=========================================="
if [ $file_count -eq 0 ]; then
    echo "No files matching the pattern were found."
    rmdir "$TEMP_DIR" 2>/dev/null || true
else
    echo "Operation completed successfully!"
    echo "Total files copied: $file_count"
    echo "Destination: $TEMP_DIR"
fi
echo "=========================================="
