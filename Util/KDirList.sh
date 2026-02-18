#!/bin/bash
# Creates a content list file to each subdirectory from the given directory recursively.
# Read and Write permissions are required for each subdirectory.
#
# Usage:
# Make it executable: chmod +x KDirList.sh
# Run with parameter: ./KDirList.sh <directory_name>

# Assign the first argument to 'DIR', defaulting to current directory ($PWD)
DIR="${1:-$PWD}"
INDEX_FILE="_nIndex.txt"

echo "Listing contents of: $DIR"
if [ -w "$DIR" ]; then
	find "$DIR" -type d  | while IFS= read -r directory;
	do
		cd "$directory"
		#Create a new index file for each subdirectory
		find  -maxdepth 1  -not -name "." -not -name $INDEX_FILE -printf "%f\t\r" |
		awk "{print substr(\$0,0,length(\$0)-1)}"  > $INDEX_FILE
		cd - > /dev/null
	done
else
	echo "Directory '$DIR' is not writable.\rCreating file index ${PWD}/$INDEX_FILE"
	find "$DIR" -not -name "." -exec readlink -f {} + > "$INDEX_FILE"

fi
