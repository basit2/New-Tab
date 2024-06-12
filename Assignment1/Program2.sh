#!/bin/bash
#Problem 1.2, Filename: Program2.sh, Author: MD Basit Alam

read -p "Enter your Basic Salary: " basic_salary

read -p "Enter your DA Rate (percentage): " da_rate

da_fraction=$(echo "scale=2; $da_rate / 100" | bc)
da_amount=$(echo "scale=2; $da_fraction * $basic_salary" | bc)
net_income=$(echo "scale=2; $da_amount + $basic_salary" | bc)

echo "-----------------------------"
echo "Basic Salary: $basic_salary"
echo "DA Rate: $da_rate%"
echo "DA Amount: $da_amount"
echo "Net Income: $net_income"
echo "-----------------------------"
