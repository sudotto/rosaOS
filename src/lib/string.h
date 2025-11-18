#ifndef STRING
#define STRING

int strlen(char* str);                           // get length of string
int strcmp(char* str, char* str2);               // compare strings for differnces (match = 0) (no match = 1)
int strclr(char* str);                           // compare strings for differnces (match = 0) (no match = 1)
void strpush(char* str, char ch);                // push char to string
void strpop(char* str);                 // pop char from string
void strcat(char* str, char* str2);              // concatenate two strings

#endif
