#!/usr/bin/env python3
#Creates a content list file to each subdirectory from the given directory recursively.
#Example:
#  python3 /path/to/dirLists.py /path/to/directory

import os
import sys

for root, dirs, files in os.walk(sys.argv[1]):
    for dr in dirs:
        dr = os.path.join(root, dr)
        open(os.path.join(dr, "_2Index.txt"), "wt").write(
            "\r\n\\\t".join(f for f in os.listdir(dr) if f != "_2Index.txt")
            )

