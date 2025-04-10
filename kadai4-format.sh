#!/bin/bash
gcc -o kadai4-time kadai4-time.c -O2

# kadai4-no.sh(kadai4.sh)を実行して得たファイルをフォーマット
./kadai4-time dfs-1000-1000-002.txt > dfs-1000-1000-002.data
./kadai4-time dfs-term-1000-1000-002.txt > dfs-term-1000-1000-002.data
./kadai4-time bfs-1000-1000-002.txt > bfs-1000-1000-002.data