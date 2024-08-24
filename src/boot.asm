bits 32
section .text
	align 4
	dd 0x1badb002                                          ; magic number
	dd 0x00                                                ; flags
	dd - (0x1badb002 + 0x00)                               ; should be zero

global start
	extern main                                            ; main in kernel.c

start:
	cli                                                    ; stop interrupts
	call main                                             ; call the kernel
	hlt                                                    ; halt CPU
