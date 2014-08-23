#include <iostream>
#include <string.h>

#include "jout.h"
#include "poker.h"

int main(int argc, char **argv) {

	
	
	// set debug mode
	if (argc > 1) {
		if(strncmp(argv[1], "-d", 2) == 0) {
			Debug::DebugEnabled = 1;
		}
	}
	
	// clear log file
	Jout out;
	out.init();

	// start game!
	Poker poker;
	poker.StartGame();
}
