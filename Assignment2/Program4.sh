#!/bin/bash
#Problem 2.4, Filename: Program4.sh, Author: MD Basit Alam
echo "Home Directory": $HOME
echo "Operating System Type: $(uname -o)"
echo "Version: $(uname -v)"
echo "Release Number: cat /proc/sys/kernel/osrelease"
echo "Kernel Version: " uname -r
echo "Current Path Setting: "
echo $PATH | tr ':' '\n'
