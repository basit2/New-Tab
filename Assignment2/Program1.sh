#!/bin/bash
#Problem 2.1, Filename: Program1.sh, Author: MD Basit Alam
ls -l
for item in *; do
	if [ -f "$item" ]; then
		echo "$item is a regular file."
	elif [ -d "$item" ]; then
		echo "$item is a directory."
	else
		echo "$item is not a regular file nor a directory."
	fi
done
