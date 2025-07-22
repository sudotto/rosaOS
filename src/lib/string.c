int strlen(char* str){                           // get length of string
	for(int i = 0; i < 512; i++){
		if(str[i] == 0){
			return i;
		}
	}
}

int strcmp(char* str, char* str2){               // compare strings for differnces (match = 0) (no match = 1)
	for(int i = 0; i < strlen(str); i++){
		if(str[i] != str2[i]){
			return 1;
		}
	}
	return 0;
}

void strcat(char* str, char* str2){              // concatenate two strings
	int offset = strlen(str);
	for(int i = 0; i < strlen(str2); i++){
		str[i + offset] = str2[i];
	}
}
