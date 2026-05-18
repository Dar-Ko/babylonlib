#!/bin/bash
#
# .SYNOPSIS
#    Verify integrity of MP3 audio files in a directory
# .USAGE
#    ./KVerifyMp3.sh [directory]
#    If directory is omitted, current directory is used.
# .DESCRIPTION
#    The script recursively finds all .mp3 files (case-insensitive) and runs
#    test on each. Any errors are written to
#    mp3-errors.txt inside the target directory. A summary is printed to stdout.
# .EXAMPLE
#    chmod +x KVerifyMp3.sh
#    ./KVerifyMp3.sh /home/user/Music


# Check for one of the required tools
# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

VERIFY_TOOL=""
if command -v mp3check &> /dev/null; then
    VERIFY_TOOL="mp3check"
    TOOL_OPTS="-e -3" # Quiet mode, just output errors
elif command -v mp3val &> /dev/null; then
    VERIFY_TOOL="mp3val"
    TOOL_OPTS="-f" # Fast check only (no fixing)
else
    echo -e "${RED}ERROR:${NC} Neither 'mp3check' nor 'mp3val' found on system."
    echo "Please install one of them:"
    echo "  Ubuntu/Debian: sudo apt install mp3check"
    echo "  Alternatively: sudo apt install mp3val"
    exit 1
fi

# Use provided directory or default to current directory
TARGET_DIR="${1:-.}"
if [ ! -d "$TARGET_DIR" ]; then
    echo "${YELLOW}ERROR:${NC} Directory '$TARGET_DIR' does not exist."
    exit 2
fi

# Path to the error log inside the target directory
ERROR_LOG="$TARGET_DIR/mp3-errors.txt"

# Clear or create new error log
> "$ERROR_LOG"

################################################################################
# Function to check MP3 file
check_mp3() {
    local file="$1"

    case "$VERIFY_TOOL" in
        mp3check)

            # Capture output and preserve exit code
            err_output=$(mp3check $TOOL_OPTS  "$file" 2>&1)
            exit_code=$?
            if [ $exit_code -ne 0 ] && [ -n "$err_output" ]; then
                # Remove first line and save error
                echo -n "$err_output" | tail -n +2
            fi
            return $exit_code
            ;;
        mp3val) # TODO:testing
            err_output=$(mp3val $TOOL_OPTS "$file" -nb 2>&1)
            exit_code=$?
            if [ $exit_code -ne 0 ]; then
                echo -n "$err_output" | grep -qi "ERROR\|CORRUPTED\|INVALID\|WRONG"
            fi
            return $exit_code
            ;;
        *)
            return 1
            ;;

    esac

    #return $result
}

# Counters for summary
total_files=0
error_files=0

echo -e "${BLUE}Verifying MP3 audio files on '$TARGET_DIR'"
echo -e "Tool used: $VERIFY_TOOL ${NC}"
echo "Scan date: $(date '+%Y-%m-%d %H:%M:%S')" >> "$ERROR_LOG"
echo "Tool used: $VERIFY_TOOL" >> "$ERROR_LOG"

while IFS= read -r -d '' mp3_file; do
    ((++total_files))
    echo -n "Checking: $mp3_file ... "

    # Check the file
    check_mp3 "$mp3_file"
    result=$?
 #   echo -e "${YELLOW}res= $result"
    if [ $result -eq 0 ]; then
        echo -e "${GREEN} ✓ OK${NC}"
    else
        echo -e "${YELLOW} ✗ INVALID${NC}"
        ((++error_files))
        # Write details to the error log
        echo "===== $mp3_file =====" >> "$ERROR_LOG"
        echo "$err_output" >> "$ERROR_LOG"
        echo "" >> "$ERROR_LOG"   # blank line separator

    fi

# Use find with -print0 to handle filenames with spaces or special characters
done < <(find "$TARGET_DIR" -type f -iname "*.mp3" -print0)

# Print summary
echo "--------------------------------"
echo "Total MP3 files found: $total_files"
echo "Files with errors:      $error_files"

if [ $error_files -eq 0 ]; then
    echo -e "${GREEN}All MP3 files are valid."
    # Remove the empty error log (optional)
    rm -f "$ERROR_LOG"
else
    echo "-------------------------------------------------" >> "$ERROR_LOG"
    echo "Total MP3 files found: $total_files" >> "$ERROR_LOG"
    echo "Files with errors:      $error_files" >> "$ERROR_LOG"

    echo "See '$ERROR_LOG' for error details."
fi

# Exit with non-zero status if any errors were found
[ $error_files -eq 0 ] && exit 0 || exit 3

