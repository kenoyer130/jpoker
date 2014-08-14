#ifndef Player_H
#define Player_H

#include <string>

#include "card.h"

class Player {
public:
	
	std::string Name;
	unsigned int Chips;

	Card HoleCards [2];
};

#endif
