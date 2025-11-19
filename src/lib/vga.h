#ifndef TEXT_H
#define TEXT_H

#define BLK 0
#define BLU 1
#define GRN 2
#define CYN 3
#define RED 4
#define PUR 5
#define ORN 6
#define WHT 7

// FUNCTION TO RETURN THE MEMORY ADDRESS BASED ON LINE AND COL

uint16_t vid_index();

// PRINT CHAR

void printc(char c);

// CLEAR SCREEN

void CLS();

// BACK SPACE

void BS();

// CRLF

void CRLF();

// PRINT STRING

void print(char *str);

// PRINTLN

void println(char *str);

#endif
