#!/bin/bash
gcc -o kadai3main kadai3main.c
array=(0 1 2 3 4 5 6 7 8 9)
for num in "${array[@]}"; do # for の後に続く変数名には $ をつけない
    ./kadai3main kadai3/bigraph${num}_input.txt >kadai3/bigraph${num}_test.txt
    diff kadai3/bigraph${num}_output.txt kadai3/bigraph${num}_test.txt # 参照するときは $ をつける
    echo ${num}
done
