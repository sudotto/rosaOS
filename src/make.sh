# compile

cflags='-nostdlib -Wno-builtin-declaration-mismatch -fno-stack-protector'

nasm -f elf32 boot.asm           -o boot.o
gcc $cflags -m32 -c   kernel.c           -o kernel.o
gcc $cflags -m32 -c   lib/memory.c       -o memory.o
gcc $cflags -m32 -c   lib/vga.c          -o vga.o
gcc $cflags -m32 -c   lib/keyboard.c     -o keyboard.o
gcc $cflags -m32 -c   lib/string.c       -o string.o
gcc $cflags -m32 -c   lib/disk.c         -o disk.o
gcc $cflags -m32 -c   lib/io.c           -o io.o
gcc $cflags -m32 -c   apps/shell/main.c  -o shell.o
gcc $cflags -m32 -c   apps/shell/cmd.c   -o cmd.o

# link

ld -m elf_i386 -T linker.ld -o rosaOS boot.o kernel.o vga.o memory.o keyboard.o string.o disk.o io.o shell.o cmd.o
dd if=/dev/zero of=disk.img bs=512 count=32768

# clean up

rm boot.o kernel.o vga.o memory.o keyboard.o string.o disk.o io.o shell.o cmd.o
