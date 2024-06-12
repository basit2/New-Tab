#!/bin/bash
#Problem 3.6, Filename: Program6.sh, Author: MD Basit Alam

echo "Files present in the current directory:"
ls -l
count=$(ls -l | grep -c ".sh$")
echo "Number of shell scripts: $count"
