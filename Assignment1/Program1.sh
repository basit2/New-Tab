#!/bin/bash
#Problem 1.1, Filename: Program1.sh, Author: MD Basit Alam

read -p "Enter the width and height of the rectangle in meters: " width height
area=$((width * height))
perimeter=$((2 * (width + height)))
echo "Area of the rectangle is: $area"
echo "Perimeter of the rectange is: $perimeter"
