#!/bin/bash
array=(0 1 2 3 4 5 6 7 8 9)
echo "brute-force-opt0"
for num in "${array[@]}"; do 
    ./brute-force kadai4/rand${num}.txt
done