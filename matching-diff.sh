#!/bin/bash

for edge in {10..20}; do
    echo edge $edge
    diff data5/brute-matching-v10-$edge.txt data5/greedy-matching-v10-$edge.txt
    echo ...........
    diff data5/brute-matching-v10-$edge.txt data5/dfs-matching-v10-$edge.txt
    diff data5/brute-matching-v10-$edge.txt data5/dfs-term-matching-v10-$edge.txt
    diff data5/brute-matching-v10-$edge.txt data5/bfs-matching-v10-$edge.txt
    echo
done

for vertex in {5..15}; do
    echo vertex $vertex
    diff data4/brute-matching-$vertex-e25.txt data4/greedy-matching-$vertex-e25.txt
    echo ...........
    diff data4/brute-matching-$vertex-e25.txt data4/dfs-matching-$vertex-e25.txt
    diff data4/brute-matching-$vertex-e25.txt data4/dfs-term-matching-$vertex-e25.txt
    diff data4/brute-matching-$vertex-e25.txt data4/bfs-matching-$vertex-e25.txt
    echo
done