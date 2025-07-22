# compile

nasm -f elf32 boot.asm           -o boot.o
gcc -nostdlib -fno-stack-protector -m32 -c   kernel.c           -o kernel.o
gcc -nostdlib -fno-stack-protector -m32 -c   memory.c           -o memory.o
gcc -nostdlib -fno-stack-protector -m32 -c   drivers/vga.c      -o vga.o
gcc -nostdlib -fno-stack-protector -m32 -c   drivers/keyboard.c -o keyboard.o
gcc -nostdlib -fno-stack-protector -m32 -c   lib/string.c       -o string.o
gcc -nostdlib -fno-stack-protector -m32 -c   apps/shell.c       -o shell.o

# link

ld -m elf_i386 -T linker.ld -o rosaOS boot.o kernel.o vga.o memory.o keyboard.o string.o shell.o

# clean up

rm boot.o kernel.o vga.o memory.o keyboard.o string.o shell.o
