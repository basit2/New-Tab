#!/bin/bash
#Problem 3.5, Filename: Program5.sh, Author: MD Basit Alam

echo "Files before renaming:"
ls -l

for file in *.sh; do
    if [ -e "$file" ]; then
        mv "$file" "${file%.sh}.exe"
        echo "Renamed $file to ${file%.sh}.exe"
    else
        echo "No .sh files found to rename."
    fi
done

echo "Files renamed."

echo "Files after renaming:"
ls -l

#Now we want to revert back the changes.
for file in *.exe; do
	if [ -e "$file" ]; then
		mv "$file" "${file%.exe}.sh"
	fi
done
