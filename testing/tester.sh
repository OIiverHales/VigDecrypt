#!/usr/bin/env bash
filename=$1
clang -Wall -Wvla -Werror -g ../vigDecrypt.c -o vigDecrypt
grep -E '^CIPHERTEXT:' $filename | cut -d':' -f2- | ./vigDecrypt