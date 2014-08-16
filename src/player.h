#ifndef Player_H
#define Player_H

#include <string>
#include <vector>

#include "card.h"

class Player {
public:

	bool AI;
	
    std::string Name;
	unsigned int Chips;

	Card HoleCard[2];
};

#endif
