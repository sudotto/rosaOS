#include <stdint.h>

#include "vga.h"

// LINE COUNTER

unsigned int line;
unsigned int col;

// FUNCTION TO RETURN THE MEMORY ADDRESS BASED ON LINE AND COL

uint16_t vid_index(){
	return (line*80+col)*2;                                // this math is too stupid to write everytime, thats why i'm abstracting this
}

// BACK SPACE

void BS(){
	col--;
	printc(' ');
	col--;
}

// CRLF

void CRLF(){
	line++;
	col = 0;
}

// CLEAR SCREEN

void CLS(){                                                // function to clear screen
	line = 0;                                              // reset line
	col = 0;                                               // reset col
	for(uint16_t i = 0; i < (80*25*2); i++){               // while i is still in screen bounds, inc i...
		printc(' ');                                       // write blank char to current address
	}
	line = 0;                                              // reset line
	col = 0;                                               // reset col
}

// PRINT CHAR

void printc(char c){
	char *video = (char *) 0xb8000;                        // video memory
	switch(c){
		case '\n':
			CRLF();
			break;
		case '\b':
			BS();
			break;
		default:
			video[vid_index()] = c;                                // asign the char slot to the character
			video[vid_index() + 1] = 0x07;                         // asign color slot to white on black
			col++;                                                 // inc col
			break;
	}
}

// PRINT STRING

void print(char *str){
	for(uint8_t i = 0; str[i] != 0; i++){                  // while i isn't null terminator inc i...
		printc(str[i]);                                // print current char
	}
}

// PRINTLN

void println(char *str){
	print(str);                                            // print
	line++;                                                // inc line
	col = 0;                                               // reset col
}
