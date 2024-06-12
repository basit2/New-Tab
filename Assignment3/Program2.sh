#!/bin/bash
#Problem 3.2, Filename: Program2.sh, Author: MD Basit Alam

file_count=0
dir_count=0
ls -l

for item in *; do
	if [ -f "$item" ]; then
		file_count=$((file_count + 1))
		echo "File: $item"
	fi
	if [ -d $item ]; then
		dir_count=$((dir_count + 1))
		echo "Directory: $item"
	fi
done

echo "Total $file_count files found in the current directory"
echo "Total $dir_count directory found inside the current directory"
