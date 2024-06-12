#!/bin/bash
#Problem 3.4, Filename: Program4.sh, Author: MD Basit Alam

echo "This is temporary file 1" > temp_file1~
echo "This is temporary file 2" > temp_file2~

echo "Files before deletion:"
ls -l

rm -f *~

echo "Temporary files deleted"

echo "Files after deletion:"
ls -l
