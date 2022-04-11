#!/bin/bash
export LD_LIBRARY_PATH=/bin/gsl/lib 
mkdir ./outputs
for filename in ./data/*.txt; do
    ./sr -D "$filename" -G 25 -N 10000 -n 500000 -d 0.001 -F 20 -f 1000 -s 100 -P constant.pop -e 8067 -a -o outputs/"$(basename -s .txt "$filename")" 
done