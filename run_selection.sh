#!/bin/bash
export LD_LIBRARY_PATH=/bin/gsl/lib 
mkdir -p ./outputs
echo "name,alpha_1_mean,alpha_1_std,alpha_2_mean,alpha_2_std" > results.csv
#./sr -D "tmp" -G 25 -N 10000 -n 500000 -d 0.001 -F 20 -f 1000 -s 100 -P constant.pop -e 8067 -a -o "outputs"

task(){
    
    ./sr -D "$1" -G 25 -N 10000 -n 500000 -d 0.001 -F 20 -f 1000 -s 100 -P constant.pop -e 8067 -a -o "$(basename -s .txt "$1")"; sleep 1.0; 
    #echo "$1"; sleep 2.0; 
}

./sr #-D tmp -G 25 -N 10000 -n 500000 -d 0.001 -F 20 -f 1000 -s 100 -P constant.pop -e 8067 -a -o tmp  #&

# N=4
# for filename in ./data/*.txt; do
# #for filename in {1..10}; do

#    #((i=i%N)); ((i++==0)) && wait
#    task "$filename"
#    #echo "$filename" 
#    ./sr -D "$filename" -G 25 -N 10000 -n 500000 -d 0.001 -F 20 -f 1000 -s 100 -P constant.pop -e 8067 -a -o "$(basename -s .txt "$filename")" & #&
    
#     #echo -n "$(basename -s .txt "$filename")", >> results.csv
    
# done

# N=4
# (
# for thing in a b c d e f g; do 
#    ((i=i%N)); ((i++==0)) && wait
#    task "$thing" & 
# done
# )