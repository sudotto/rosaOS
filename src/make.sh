nasm boot.asm -o boot.bin                                            # compile bootloader to binary
nasm test.asm -o test.bin                                            # compile boot test to binary

dd if=/dev/zero of=os.img bs=512 count=2880                          # create a disk img of zeroes
dd if=boot.bin of=os.img bs=512 conv=notrunc                         # put bootloader binary into disk img
dd if=test.bin of=os.img bs=512 conv=notrunc                         # put boot test binary into disk img
