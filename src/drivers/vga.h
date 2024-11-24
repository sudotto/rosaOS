#ifndef TEXT_H
#define TEXT_H

// CLEAR SCREEN

void cls();

// FUNCTION TO RETURN THE MEMORY ADDRESS BASED ON LINE AND COL

unsigned int vid_index();

// PRINT CHAR

void printc(char c);

// PRINT STRING

void print(char *str);

// PRINTLN

void println(char *str);

#endif
