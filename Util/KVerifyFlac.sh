#!/bin/bash
cd ~/Public/Music
if [[ -f flac-errors.txt ]]; then
	rm flac-errors.txt;
fi
touch flac-errors.txt
shopt -s globstar
for file in ./**/*.flac; do
	flac -wst "$file" 2>/dev/null || printf '%3d %s\n' "$?" "$file" >> flac-errors.txt;
done
