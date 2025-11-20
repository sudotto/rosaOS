#ifndef STRING
#define STRING

int strlen(char* str);                           // get length of string
int strcmp(char* str, char* str2);               // compare strings for differnces (match = 0) (no match = 1)
int strclr(char* str);                           // compare strings for differnces (match = 0) (no match = 1)
void strpush(char* str, char ch);                // push char to string
void strpop(char* str);                          // pop char from string
void strcpy(char* str, char* str2);              // copy string 
void strcat(char* str, char* str2);              // concatenate two strings
void strcut(char* str, char* dest, int i);       // cut a string at index 

#endif
