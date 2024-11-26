# compile

nasm -f elf32 boot.asm           -o boot.o
gcc -m32 -c   kernel.c           -o kernel.o
gcc -m32 -c   memory.c           -o memory.o
gcc -m32 -c   drivers/vga.c              -o vga.o
gcc -m32 -c   drivers/keyboard.c -o keyboard.o

# link

ld -m elf_i386 -T linker.ld -o rosaOS boot.o kernel.o vga.o memory.o keyboard.o

# clean up

rm boot.o kernel.o vga.o memory.o keyboard.o
