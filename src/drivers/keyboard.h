#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

// GET KEYBOARD STATUS

uint8_t kb_status();

// READ KEYBOARD DATA

uint8_t kb_read();

// GET CHAR FROM KEYBOARD

char* kb_keypressed();

#endif
