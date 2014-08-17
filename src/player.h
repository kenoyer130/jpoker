#ifndef Player_H
#define Player_H

#include <string>
#include <vector>
#include <memory>

#include "card.h"
#include "ai.h"

class Player {
public:

	std::unique_ptr<AI> AI;

	bool Dealer;
	bool BigBlind;
	bool SmallBlind;

	bool Folded;
	
    std::string Name;
	unsigned int Chips;
	
	Card HoleCard[2];

	int BetAmount;

	// subtracts the bet and sets the bet amount.
	// if the bet is more then chips then returns all chips
	int bet(int amount);
};

#endif
