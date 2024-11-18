# compile

nasm -f elf32 boot.asm           -o boot.o
gcc -m32 -c   kernel.c           -o kernel.o
gcc -m32 -c   text.c             -o text.o
gcc -m32 -c   port.c             -o port.o
gcc -m32 -c   drivers/keyboard.c -o keyboard.o

# link

ld -m elf_i386 -T linker.ld -o rosaOS boot.o kernel.o text.o port.o keyboard.o

# clean up

rm boot.o kernel.o text.o port.o keyboard.o
