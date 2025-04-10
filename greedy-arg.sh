#!/bin/bash
# 点の数を変化させる場合 (辺の数は25本)
# for num in {0..9}; do 
#     ./greedy brute-graph/rand$1-${num}.txt
# done

# 辺の数を変化させる場合 (点の数は10*2 = 20個)
for num in {0..9}; do 
    ./greedy brute-graph/rand-e$1-${num}.txt
done