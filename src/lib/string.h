#ifndef STRING
#define STRING

int strlen(char* str);                           // get length of string
int strcmp(char* str, char* str2);               // compare strings for differnces (match = 0) (no match = 1)
void strclr(char* str);                          // compare strings for differnces (match = 0) (no match = 1)
void strclrfull(char* str, int len);             // zero a string but like... harder
void strpush(char* str, char ch);                // push char to string
void strpop(char* str);                          // pop char from string
void strcpy(char* str, char* dest);              // copy string 
void strcat(char* str, char* src);               // concatenate two strings
void strcut(char* str, char* dest, int i);       // cut a string at index 

#endif
