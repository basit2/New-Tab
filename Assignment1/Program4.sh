#!/bin/bash
#Problem 1.4, Filename: Program4.sh, Author: MD Basit Alam
echo "Please enter a five-digit number:"
read num
if [[ $num =~ ^[0-9]{5}$ ]]; then
	reversed_num=$(echo "$num" | rev)
	echo "Reverse of $num is: $reversed_num"
else
	echo "Invalid input. Please enter a valid five-digit number."
fi
