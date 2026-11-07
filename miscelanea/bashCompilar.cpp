/*
#!/bin/bash

FILENAME="${1%.*}"
g++ -std=c++20 -O2 -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal \
    -fsanitize=address,undefined -fno-sanitize-recover=all \
    -g "$1" -o main

# ./"$FILENAME" < in.txt > out.txt
./main < in.txt > out.txt
*/


