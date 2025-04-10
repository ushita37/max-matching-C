#!/bin/bash
gcc -o randgen kadai4/randgen.c -O0 # no optimization
gcc -o kadai3main_o0 kadai3main.c -O0
gcc -o kadai5main_o0 kadai5main.c -O0
gcc -o kadai5-bfs_o0 kadai5-bfs.c -O0

#実行時間を安定させるために初回の実行はファイルに書き込まず、そのままターミナルに出す
array=(0 1 2 3 4 5 6 7 8 9)
for num in "${array[@]}"; do # for の後に続く変数名には $ をつけない
    ./randgen 500 500 0.002 > kadai4/rand${num}.txt
done

echo "dfs-optimization 0"
(time for num in "${array[@]}"; do 
    ./kadai3main_o0 kadai4/rand${num}.txt
done)

echo -e "\ndfs-terminal-optimization 0"
(time for num in "${array[@]}"; do 
    ./kadai5main_o0 kadai4/rand${num}.txt
done)

echo -e "\nbfs-optimization 0"
(time for num in "${array[@]}"; do 
    ./kadai5-bfs_o0 kadai4/rand${num}.txt
done)

#サブシェル呼び出し
array=(0 1 2 3 4 5 6 7 8 9)
for num in "${array[@]}"; do # for の後に続く変数名には $ をつけない
    ./kadai4.sh
done
