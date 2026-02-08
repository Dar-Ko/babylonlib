#!/bin/bash
# Creates a content list file to each subdirectory from the given directory recursively.
# note : this assumes you run the script from top-most directory
find  -type d  | while IFS= read -r directory;
do
    cd "$directory"
    find  -maxdepth 1  -not -name "." -not -name "_nIndex.txt" -printf "%f," |
    awk "{print substr(\$0,0,length(\$0)-1)}"  > _nIndex.txt
    cd - > /dev/null
done
