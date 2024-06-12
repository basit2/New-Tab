#!/bin/bash
#Problem 2.3, Filename: Program3.sh, Author: MD Basit Alam
grep "vendor_id" /proc/cpuinfo | uniq
grep "model name" /proc/cpuinfo | uniq
grep "cache size" /proc/cpuinfo | uniq
grep "cpu MHz" /proc/cpuinfo | uniq
