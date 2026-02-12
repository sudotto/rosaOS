#include "io.h"

int strlen(char* str){                           // get length of string
	for(int i = 0; i < 512; i++){
		if(str[i] == 0){
			return i;
		}
	}
}

int strcmp(char* str, char* str2){               // compare strings for differnces (match = 0) (beyond 0 is index before it doesn't match + 1 ie, (gate, game) = 2)
	for(int i = 0; i < strlen(str); i++){
		if(str[i] != str2[i]){
			return i+1;
		}
	}
	if(strlen(str) == strlen(str2)){
		return 0;
	} else {
		return strlen(str);
	}
}

void strclr(char* str){                         // zero a string
	int len = strlen(str);
	for(int i = 0; i < len; i++){
		str[i] = 0;
	}
}

void strclrfull(char* str, int len){                         // zero a string but like... harder
	for(int i = 0; i < len; i++){
		str[i] = 0;
	}
}

void strpush(char* str, char ch){              // put a char on a string
	int offset = strlen(str);
	str[offset] = ch;
}

void strpop(char* str){                        // take a char off a string
	int offset = strlen(str);
	str[offset - 1] = 0;
}

void strcpy(char* str, char* dest){              // copy str into dest 
	for(int i = 0; i < strlen(str); i++){
		dest[i] = str[i];
	}
}

void strcat(char* str, char* src){              // concatenate two strings
	int offset = strlen(str);
	for(int i = 0; i < strlen(src); i++){
		str[i + offset] = src[i];
	}
}

void strcut(char* str, char* dest, int i){              // cut a string at index
	int len = strlen(str) - i;
	for(int j = 0; j < len; j++){
		dest[j] = str[j + i];
		str[j + i] = 0;
	}
}

/*
void strcut(char* str, char* dest, int i){              // cut a string at index
	int len = strlen(str) - i;
	for(int j = 0; j < len; j++){
		dest[j] = str[j + i];
		str[j + i] = '\0';
	}
}
*/
