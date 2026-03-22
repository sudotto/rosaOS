#include <stdint.h>
#include <stdbool.h>

#include "vga.h"
#include "keyboard.h"
#include "string.h"

#include "io.h"

unsigned int line = 0;
unsigned int col = 0;

bool fucky_backspace = false;

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

void print_cursor(){
	vga_write('_', fg, bg, vga_index(col, line));
}

void printc(char c){
	vga_write(c, bg, fg, vga_index(col, line));
	col++;
}

void print(char *str){
	for(uint8_t i = 0; str[i] != 0; i++){                  // while i isn't null terminator inc i...
		switch(str[i]){
			case '#': // rosaOS version of escape codes, #n is newline #b is bs #c is color
				i++;
				switch(str[i]){
					case 'n': 
						if(line >= 25 - 1){
							vga_scroll(1);
						} else {
							vga_write(' ', bg, fg, vga_index(col, line));
							line++;
						}
						col = 0;
						break;
					case 'b': 
						if(col == 0){
							col = VGA_COLS - 1;
							line--;
							while(vga_mem[vga_index(col, line) - 1] == '\0'){
								col--;
							}
							col++;
						} else {
							vga_write(' ', bg, fg, vga_index(col, line));
							col--;
							vga_write(' ', bg, fg, vga_index(col, line));
						}
						break;
					case 'c': 
						i++;
						bg = str[i] - '0';
						i++;
						fg = str[i] - '0';
						break;
					case '#':
					default:
						break;
				}
				break;
			default:
				printc(str[i]);
				break;
		}
	}
}

void input(char* str){
	char scan;
	while(1){
		print_cursor();
		scan = kb_read();
		switch(scan){                        // if scancode is...
			case 14:                         // the backspace key...
				if(strlen(str) != 0 || fucky_backspace == true){
					strpop(str);
					print("#b");
				}
				break;
			case 28:                         // the enter key...
				return;
		}
		if(kb_translate(scan)){              // if char is typable...
			char key = kb_translate(scan);
			printc(key);                     // print the char
			strpush(str, key);
		}
	}
}
