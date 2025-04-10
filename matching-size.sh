#!/bin/bash

gcc -o matching-size matching-size.c -O2

for edge in {10..20}; do
    ./matching-size data5/brute-matching-v10-$edge.txt > data5/brute-matching-v10-$edge.data
    ./matching-size data5/greedy-matching-v10-$edge.txt > data5/greedy-matching-v10-$edge.data
    ./matching-size data5/dfs-matching-v10-$edge.txt > data5/dfs-matching-v10-$edge.data
    ./matching-size data5/dfs-term-matching-v10-$edge.txt > data5/dfs-term-matching-v10-$edge.data
    ./matching-size data5/bfs-matching-v10-$edge.txt > data5/bfs-matching-v10-$edge.data
done

for vertex in {5..15}; do
    ./matching-size data4/brute-matching-$vertex-e25.txt > data4/brute-matching-$vertex-e25.data
    ./matching-size data4/greedy-matching-$vertex-e25.txt > data4/greedy-matching-$vertex-e25.data
    ./matching-size data4/dfs-matching-$vertex-e25.txt > data4/dfs-matching-$vertex-e25.data
    ./matching-size data4/dfs-term-matching-$vertex-e25.txt > data4/dfs-term-matching-$vertex-e25.data
    ./matching-size data4/bfs-matching-$vertex-e25.txt > data4/bfs-matching-$vertex-e25.data
done
