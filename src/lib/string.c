int strlen(char* str){                           // get length of string
	for(int i = 0; i < 512; i++){
		if(str[i] == '\0'){
			return i;
		}
	}
}

int strcmp(char* str, char* str2){               // compare strings for differnces (match = 0) (beyond 0 is index before it doesn't match + 1 ie, (gate, game) = 2)
	//if(strlen(str) != strlen(str2)){
	//	return 1;
	//}
	for(int i = 0; i < strlen(str); i++){
		if(str[i] != str2[i]){
			return i+1;
		}
	}
	return 0;
}

int strclr(char* str){
	int len = strlen(str);
	for(int i = 0; i < len; i++){
		str[i] = '\0';
	}
	return 0;
}

void strpush(char* str, char ch){              // put a char on a string
	int offset = strlen(str);
	str[offset] = ch;
}

void strpop(char* str){                        // put a char on a string
	int offset = strlen(str);
	str[offset - 1] = '\0';
}

void strcpy(char* str, char* str2){              // copy string 
	for(int i = 0; i < strlen(str); i++){
		str2[i] = str[i];
	}
}

void strcat(char* str, char* str2){              // concatenate two strings
	int offset = strlen(str);
	for(int i = 0; i < strlen(str2); i++){
		str[i + offset] = str2[i];
	}
}

void strcut(char* str, char* dest, int i){              // cut a string at index
	int len = strlen(str) - i;
	for(int j = 0; j < len; j++){
		dest[j] = str[j + i];
		str[j + i] = '\0';
	}
}
