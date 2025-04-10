#!/bin/bash

array=(0 1 2 3 4 5 6 7 8 9)
for num in "${array[@]}"; do # for の後に続く変数名には $ をつけない
    ./randgen 500 500 0.002 > kadai4/rand${num}.txt
done

echo "dfs-optimization 0"
(time for num in "${array[@]}"; do 
    ./kadai3main_o0 kadai4/rand${num}.txt
done) 2>> dfs-500-500-002.txt

echo -e "\ndfs-terminal-optimization 0"
(time for num in "${array[@]}"; do 
    ./kadai5main_o0 kadai4/rand${num}.txt
done) 2>> dfs-term-500-500-002.txt

echo -e "\nbfs-optimization 0"
(time for num in "${array[@]}"; do 
    ./kadai5-bfs_o0 kadai4/rand${num}.txt
done) 2>> bfs-500-500-002.txt