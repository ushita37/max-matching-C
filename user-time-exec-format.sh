#!/bin/bash
gcc -o randgen kadai4/randgen.c -O0 # no optimization
gcc -o kadai3main_o0 kadai3main.c -O0
gcc -o kadai5main_o0 kadai5main.c -O0
gcc -o kadai5-bfs_o0 kadai5-bfs.c -O0

#実行時間を安定させるために初回の実行はファイルに書き込まず、そのままターミナルに出す
array=(0 1 2 3 4 5 6 7 8 9)
for num in "${array[@]}"; do # for の後に続く変数名には $ をつけない
    ./randgen 1000 1000 0.0015 > kadai4/rand${num}.txt
done

echo "dfs-user-optimization 0"
(time for num in "${array[@]}"; do 
    ./kadai3main_o0 kadai4/rand${num}.txt
done)

echo -e "\ndfs-user-terminal-optimization 0"
(time for num in "${array[@]}"; do 
    ./kadai5main_o0 kadai4/rand${num}.txt
done)

echo -e "\nbfs-user-optimization 0"
(time for num in "${array[@]}"; do 
    ./kadai5-bfs_o0 kadai4/rand${num}.txt
done)

#サブシェル呼び出し
for num in "${array[@]}"; do # for の後に続く変数名には $ をつけない
    ./randgen 1000 1000 0.0015 > kadai4/rand${num}.txt
done

(time ./dfs.sh) 2> data2/dfs-1000-1000-0015.txt
(time ./dfs-term.sh) 2> data2/dfs-term-1000-1000-0015.txt
(time ./bfs.sh) 2> data2/bfs-1000-1000-0015.txt 

gcc -o user-time user-time.c -O2

# dfs.sh, dfs-term.sh, bfs.shを実行して得たファイルをフォーマット
./user-time data2/dfs-1000-1000-0015.txt > data2/dfs-user-1000-1000-0015.data
./user-time data2/dfs-term-1000-1000-0015.txt > data2/dfs-term-user-1000-1000-0015.data
./user-time data2/bfs-1000-1000-0015.txt > data2/bfs-user-1000-1000-0015.data

# 実行する順番

# 2000-2000-002
# 2250-2250-002
# 2500-2500-002
# 2750-2750-002
# 3000-3000-002

# 1000-1000-0040
# 1000-1000-0045
# 1000-1000-0050
# 1000-1000-0055
# 1000-1000-0060


