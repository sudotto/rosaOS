nasm -f elf32 boot.asm -o boot.o
gcc -m32 -c kernel.c -o kernel.o
ld -m elf_i386 -T linker.ld -o crabOS boot.o kernel.o
