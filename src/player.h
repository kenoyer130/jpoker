#ifndef Player_H
#define Player_H

#include <string>
#include <vector>

#include "card.h"

class Player {
public:

	bool AI;

	bool Dealer;
	bool BigBlind;
	bool SmallBlind;
	
    std::string Name;
	unsigned int Chips;

	Card HoleCard[2];
};

#endif
