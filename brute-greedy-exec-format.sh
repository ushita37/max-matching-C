#!/bin/bash

gcc -o brute-force brute-force.c -O0
gcc -o greedy greedy.c -O0
gcc -o kadai3main_o0 kadai3main.c -O0
gcc -o kadai5main_o0 kadai5main.c -O0
gcc -o kadai5-bfs_o0 kadai5-bfs.c -O0

# 点の数を変化させる場合 (辺の数は25本)
# # 引数$1は、入力するグラフのXの要素数(5~15)

# (time ./brute-arg.sh $1) 2> data4/brute-force-$1-e25.txt > data4/brute-matching-$1-e25.txt
# (time ./greedy-arg.sh $1) 2> data4/greedy-$1-e25.txt > data4/greedy-matching-$1-e25.txt
# (time ./dfs-arg.sh $1) 2> data4/dfs-$1-e25.txt > data4/dfs-matching-$1-e25.txt
# (time ./dfs-term-arg.sh $1) 2> data4/dfs-term-$1-e25.txt > data4/dfs-term-matching-$1-e25.txt
# (time ./bfs-arg.sh $1) 2> data4/bfs-$1-e25.txt > data4/bfs-matching-$1-e25.txt

gcc -o user-time user-time.c -O2

# # 実行して得た.txtファイルをフォーマット
# ./user-time data4/brute-force-$1-e25.txt > data4/brute-force-$1-e25.data
# ./user-time data4/greedy-$1-e25.txt > data4/greedy-$1-e25.data
# ./user-time data4/dfs-$1-e25.txt > data4/dfs-$1-e25.data
# ./user-time data4/dfs-term-$1-e25.txt > data4/dfs-term-$1-e25.data
# ./user-time data4/bfs-$1-e25.txt > data4/bfs-$1-e25.data



# 辺の数を変化させる場合 (点の数は10*2 = 20個)
for arg in {10..20}; do
    (time ./brute-arg.sh $arg) 2> data5/brute-force-v10-$arg.txt > data5/brute-matching-v10-$arg.txt
    (time ./greedy-arg.sh $arg) 2> data5/greedy-v10-$arg.txt > data5/greedy-matching-v10-$arg.txt
    (time ./dfs-arg.sh $arg) 2> data5/dfs-v10-$arg.txt > data5/dfs-matching-v10-$arg.txt
    (time ./dfs-term-arg.sh $arg) 2> data5/dfs-term-v10-$arg.txt > data5/dfs-term-matching-v10-$arg.txt
    (time ./bfs-arg.sh $arg) 2> data5/bfs-v10-$arg.txt > data5/bfs-matching-v10-$arg.txt

    ./user-time data5/brute-force-v10-$arg.txt > data5/brute-force-v10-$arg.data
    ./user-time data5/greedy-v10-$arg.txt > data5/greedy-v10-$arg.data
    ./user-time data5/dfs-v10-$arg.txt > data5/dfs-v10-$arg.data
    ./user-time data5/dfs-term-v10-$arg.txt > data5/dfs-term-v10-$arg.data
    ./user-time data5/bfs-v10-$arg.txt > data5/bfs-v10-$arg.data
done

