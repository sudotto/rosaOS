#include <stdint.h>

#include "vga.h"

#include "io.h"

unsigned int line = 0;
unsigned int col = 0;

int bg = BLK;
int fg = WHT;

void print_clear(){                                              // function to clear screen
	line = 0;                                              // reset line
	col = 0;                                               // reset col
	for(uint16_t i = 0; i < (VGA_COLS*VGA_LINES*2); i++){  // while i is still in screen bounds, inc i...
		print(" ");                                        // write blank char to current address
	}
	line = 0;                                              // reset line
	col = 0;                                               // reset col
}

void printc(char c){
	vga_write(c, bg, fg, vga_index(line, col));
	col++;
}

void print(char *str){
	for(uint8_t i = 0; str[i] != 0; i++){                  // while i isn't null terminator inc i...
		switch(str[i]){
			case '\n':
				vga_write(' ', bg, fg, vga_index(line, col));
				line++;
				col = 0;
				break;
			case '\b':
				if(col == 0){
					col = VGA_COLS - 1;
					line--;
					while(vga_mem[vga_index(line, col) - 1] == ' '){
						col--;
					}
					col++;
				} else {
					col--;
					vga_write(' ', bg, fg, vga_index(line, col));
				}
				break;
			case '!': // rosaOS escape code for color
				i++;
				bg = str[i] - '0';
				i++;
				fg = str[i] - '0';
				break;
			default:
				vga_write(str[i], bg, fg, vga_index(line, col));
				col++;                                                 // inc col
				break;
		}
	}
}
