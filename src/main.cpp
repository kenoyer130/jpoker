#include <iostream>

#include "jout.h"
#include "poker.h"

int main() {

	// clear log file
	Jout out;
	out.init();
	
	Poker poker;
	poker.StartGame();
}
