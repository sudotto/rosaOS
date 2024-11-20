#include <stdint.h>
#include <stdbool.h>

#include "../../text.h"
#include "../../drivers/keyboard.h"

// SHELL MAIN

unsigned int main(){
	bool running = true;
	println("Clam Shell");
	while(running){
		print("~$ ");
		kb_read();
	}
	return 0;
}
