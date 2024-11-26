#include "vga.h"

// LINE COUNTER

unsigned int line;
unsigned int col;

// FUNCTION TO RETURN THE MEMORY ADDRESS BASED ON LINE AND COL

unsigned int vid_index(){
	return (line*80+col)*2;                                // this math is too stupid to write everytime, thats why i'm abstracting this
}

// PRINT CHAR

void printc(char c){
	char *video = (char *) 0xb8000;                        // video memory
	video[vid_index()] = c;                                // asign the char slot to the character
	video[vid_index() + 1] = 0x07;                         // asign color slot to white on black
	col++;                                                 // inc col
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
	for(unsigned int i = 0; i < (80*25*2); i++){           // while i is still in screen bounds, inc i...
		printc(' ');                                       // write blank char to current address
	}
	line = 0;                                              // reset line
	col = 0;                                               // reset col
}

// PRINT STRING

void print(char *str){
	for(unsigned int i = 0; str[i] != 0; i++){             // while i isn't null terminator inc i...
		if(str[i] == "\n"){                                // if current char is CRLF...
			line++;                                        // inc line
			col = 0;                                       // reset col
		} else {                                           // if character is anything else...
			printc(str[i]);                                // print current char
		}
	}
}

// PRINTLN

void println(char *str){
	print(str);                                            // print
	line++;                                                // inc line
	col = 0;                                               // reset col
}
