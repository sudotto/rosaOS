org 0x7c00

xor ax, ax
mov ds, ax

mov ah, 0x02
mov al, 1
mov ch, 0
mov cl, 2
mov dh, 0
xor bx, bx
mov es, bx
mov bx, 0x7e00
int 0x13
jmp 0x7e00

times 510-($-$$) db 0 
dw 0x0AA55
