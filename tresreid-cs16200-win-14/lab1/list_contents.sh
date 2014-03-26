#!/bin/bash

PASSED=$1
cd $PASSED 
find . -type f -printf "%h\n" | cut -d/ -f-2 | sort | uniq -c |sort -rn
wc -l *.txt


exit 0