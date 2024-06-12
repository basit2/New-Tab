#!/bin/bash
#Problem 3.1, Filename: Program1.sh, Author: MD Basit Alam

echo "Please enter the path to the input file:"
read input_file

if [ ! -f "$input_file" ]; then
	echo "File '$input_file' does not exist."
	exit 1
fi
ln=0
while read -r line; do
	sum=0
	for num in $line; do
		sum=$((sum + num))
	done
	ln=$((ln + 1))
	echo "Sum of integers in line '$line': $sum"
done <"$input_file"
