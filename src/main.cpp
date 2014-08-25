#include <iostream>
#include <string.h>

#include "jout.h"
#include "poker.h"

int main(int argc, char **argv) {
	
	bool autoMode {false};

	for (int i = 0; i < argc; i++) {

		if(strncmp(argv[i], "-d", 2) == 0) {
			Debug::DebugEnabled = 1;
		}

		if(strncmp(argv[i], "-a", 2) == 0) {
			autoMode = true;
		}
	}
	
	// clear log file
	Jout out;
	out.init();

	// start game!
	Poker poker(autoMode);
	poker.StartGame();
}
