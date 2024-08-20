nasm boot.asm -o boot.bin                                            # compile bootloader to binary

dd if=/dev/zero of=os.img bs=512 count=2880                          # create a disk img of zeroes
dd if=boot.bin of=os.img bs=512 conv=notrunc                         # put bootloader binary into disk img
