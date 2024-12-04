bits 32
section .data                                              ; data section

gdt_start:
	dd 0x00000000                                          ; null limit
	dd 0x00000000                                          ; null base and access
	
	dd 0x0000FFFF                                          ; text limit
	dd 0x00CF9A00                                          ; text base and access
	
	dd 0x0000FFFF                                          ; data limit
	dd 0x00CF9200                                          ; data base and access

gdt_end:

gdt:
	dw gdt_end - gdt_start - 1                             ; size of gdt
	dd gdt_start                                           ; location of the gdt 

section .text                                              ; text/code section
	align 4
	dd 0x1badb002                                          ; magic number
	dd 0x00                                                ; flags
	dd - (0x1badb002 + 0x00)                               ; should be zero

global start
	extern main                                            ; main in kernel.c

start:
	cli                                                    ; stop interrupts
	lgdt [gdt]                                             ; load gdt
	mov ax, 0x08
	mov ds, ax
	mov eax, cr0                                           ; put cr0 into eax
	or eax, 1                                              ; enable protected mode bit
	mov cr0, eax                                           ; put it back into cr0
	call main                                              ; call the kernel
	hlt                                                    ; halt CPU
