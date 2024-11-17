#include "text.h"

// LINE COUNTER

unsigned int* cur_line;

// CLEAR SCREEN

void cls(){                                                // function to clear screen
	char *video = (char *) 0xb8000;                        // video memory
	unsigned int i = 0;                                    // integer for index 
	while(i < (80*25*2)){                                  // while in screen bounds
		video[i] = ' ';                                    // character slot in vid mem is blank
		i++;                                               // inc index
		video[i] = 0x07;                                   // color slot in vid mem is white on black
		i++;                                               // inc index
	}
	*cur_line = 0;                                         // reset line
}

// PRINT STRING

unsigned int print(char *str){
	char *video = (char *) 0xb8000;                        // video memory
	unsigned int i = 0;                                    // integer for index
	unsigned int line = *cur_line;                         // set line to the current line
	i = (line*80*2);                                       // set position in mem
	while(*str != 0){                                      // check for end of str
		if(*str=='\n'){                                    // check for newline
			line++;                                        // inc line
			i = (line*80*2);                               // set position in mem
			*str++;                                        // next char in str
		} else {                                           // if normal char
			video[i] = *str;                               // print the char
			*str++;                                        // next char in str
			i++;                                           // inc index
			video[i] = 0x07;                               // set color slot to white on black
			i++;                                           // inc index
		}
	}
	return 1;                                              // success!
}

// PRINTLN

unsigned int println(char *str){
	if(!print(str)){                                       // if print fails...
		return 0;                                          // return fail
	}
	*cur_line += 1;                                        // inc line
	return 1;                                              // success
}
