#ifndef VGA_H
#define VGA_H

#define BLK 0
#define BLU 1
#define GRN 2
#define CYN 3
#define RED 4
#define PUR 5
#define ORN 6
#define WHT 7

#define VGA_LINES 25
#define VGA_COLS 80

extern char *vga_mem;                        // video memory

uint16_t vga_index(int x, int y);
void vga_write(char c, int bg, int fg, int i);

#endif
