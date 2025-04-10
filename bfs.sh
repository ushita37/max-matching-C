#!/bin/bash
array=(0 1 2 3 4 5 6 7 8 9)
echo "bfs-optimization 0"
for num in "${array[@]}"; do 
    ./kadai5-bfs_o0 kadai4/rand${num}.txt
done