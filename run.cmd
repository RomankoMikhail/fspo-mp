make -f makefile.win clean
make -f makefile.win
nasm -f bin boot.asm -o boot.oa
copy /b boot.oa+kernel.o disk.img
