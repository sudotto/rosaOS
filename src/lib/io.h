#ifndef IO_H
#define IO_H

#include <stdbool.h>

extern bool fucky_backspace;

void print_clear();
void print_cursor();
void printc(char c);
void print(char *str);
void input(char *str);

#endif
