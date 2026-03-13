#!/bin/bash
###############################################################################
# .SYNOPSIS
# Find text files containing specific phrases with various filtering
# and display options.
# .USAGE
# Make it executable: 
#  chmod +x KFindText.sh
#  ./KFindText.sh [options] "phrase" [directory]
#  .EXAMPLE
# ./KFindText.sh -i -p "*.tsv" "Item No" ~/projects

# Default values
SEARCH_DIR="."
CASE_SENSITIVE=1
RECURSIVE=1
SHOW_LINE_NUMBERS=0
COUNT_ONLY=0
FILE_PATTERN="*.txt"

show_help() {
    cat << EOF
Usage: $0 [options] "search phrase" [directory]

Options:
    -h, --help          Show this help message
    -i, --ignore-case   Case insensitive search
    -n, --line-numbers  Show line numbers
    -c, --count         Only show count of matches per file
    -p, --pattern PAT   File pattern (default: *.txt)
    --no-recursive      Don't search subdirectories
    
Examples:
    $0 "hello world"                    # Search in current dir
    $0 -i "error log" /var/logs         # Case insensitive search
    $0 -n "TODO" ~/projects              # Show line numbers
    $0 -p "*.md" "# Introduction" docs   # Search markdown files
EOF
}

# Parse options
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -i|--ignore-case)
            CASE_SENSITIVE=0
            shift
            ;;
        -n|--line-numbers)
            SHOW_LINE_NUMBERS=1
            shift
            ;;
        -c|--count)
            COUNT_ONLY=1
            shift
            ;;
        -p|--pattern)
            FILE_PATTERN="$2"
            shift 2
            ;;
        --no-recursive)
            RECURSIVE=0
            shift
            ;;
        -*)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
        *)
            break
            ;;
    esac
done

# Get search phrase and directory
SEARCH_PHRASE="$1"
SEARCH_DIR="${2:-.}"

if [ -z "$SEARCH_PHRASE" ]; then
    echo "Error: Please provide a search phrase"
    show_help
    exit 1
fi

# Build grep command
GREP_CMD="grep"
if [ $RECURSIVE -eq 1 ]; then
    GREP_CMD="$GREP_CMD -r"
fi

if [ $CASE_SENSITIVE -eq 0 ]; then
    GREP_CMD="$GREP_CMD -i"
fi

if [ $SHOW_LINE_NUMBERS -eq 1 ]; then
    GREP_CMD="$GREP_CMD -n"
fi

if [ $COUNT_ONLY -eq 1 ]; then
    GREP_CMD="$GREP_CMD -c"
fi

GREP_CMD="$GREP_CMD --include=\"$FILE_PATTERN\""

echo "Searching for '$SEARCH_PHRASE' in $SEARCH_DIR (pattern: $FILE_PATTERN)..."
echo "-----------------------------------"

# Execute search
eval $GREP_CMD "$SEARCH_PHRASE" "$SEARCH_DIR" 2>/dev/null || {
    echo "No matches found."
    exit 0
}