#!/bin/bash
export LD_LIBRARY_PATH=/bin/gsl/lib 
mkdir -p ./outputs
echo "name,alpha_1_mean,alpha_1_std,alpha_2_mean,alpha_2_std" > results.csv
#./sr -D "tmp" -G 25 -N 10000 -n 500000 -d 0.001 -F 20 -f 1000 -s 100 -P constant.pop -e 8067 -a -o "outputs"
for filename in ./data/*.txt; do
    echo "$filename" 
    #echo -n "$(basename -s .txt "$filename")", >> results.csv
    ./sr -D "$filename" -G 25 -N 10000 -n 500000 -d 0.001 -F 20 -f 1000 -s 100 -P constant.pop -e 8067 -a -o "$(basename -s .txt "$filename")" #>> results.csv
done