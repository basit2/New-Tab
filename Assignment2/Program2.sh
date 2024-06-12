#!/bin/bash
#Problem 2.2, Filename: Program2.sh, Author: MD Basit Alam
IFS=":"
read -ra DIRS <<<"$PATH"
for dir in "${DIRS[@]}"; do
	echo "Directory : $dir"
	if [ -d "$dir" ]; then
		ls -ldh $dir
	else
		echo "Directory Doesn't exist"
	fi
done
