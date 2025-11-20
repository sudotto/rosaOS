#include <stdint.h>

#include "vga.h"

// FUNCTION TO RETURN THE MEMORY ADDRESS BASED ON LINE AND COL

char *vga_mem = (char*)0xb8000;                        // video memory

uint16_t vga_index(int x, int y){
	return (x*VGA_COLS+y)*2;                          // this math is too stupid to write everytime, thats why i'm abstracting this
}

void vga_write(char c, int bg, int fg, int i){
	vga_mem[i] = c;                                // asign the char slot to the character
	vga_mem[i+1] = (bg << 4) | fg;                        // asign color slot to fg on bg
}
