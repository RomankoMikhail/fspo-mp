#!/bin/sh
make clean
make
nasm -f bin boot.asm -o boot.oa
cat boot.oa > disk.img
cat kernel.o >> disk.img