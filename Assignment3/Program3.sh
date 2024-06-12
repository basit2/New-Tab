#!/bin/bash
#Problem 3.3, Filename: Program3.sh, Author: MD Basit Alam

total_bytes=0

for item in *; do
	if [ -f $item ]; then
		size=$(ls -l "$item" | awk '{print $5}')
		echo "$item : ${size}B"
		total_bytes=$((total_bytes + size))
	fi
done

echo "Total bytes used ${total_bytes}B"
