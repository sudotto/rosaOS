#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

// GET KEYBOARD STATUS

uint8_t kb_status();

// READ KEYBOARD DATA

uint8_t kb_read();

// TRANSLATE SCANCODE

char kb_translate(uint8_t scancode);

#endif
