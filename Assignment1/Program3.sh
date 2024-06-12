#!/bin/bash
#Problem 1.3, Filename: Program3.sh, Author: MD Basit Alam
echo "Please enter a five-digit number:"
read num
sum=0
while [ $num -gt 0 ]; do
	digit=$((num % 10))
	sum=$((sum + digit))
	num=$((num / 10))
done
echo "Sum of the digits of the entered number is: $sum"
