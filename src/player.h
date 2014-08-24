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

	bool Folded {false};
	
    std::string Name {""};
	unsigned int Chips {0};
	
	Card HoleCard[2];

	int BetAmount{0};

	// subtracts the bet and sets the bet amount.
	// if the bet is more then chips then returns all chips
	int bet(int amount);

	Player(){}

     Player(Player const& other)
		 : AI(other.AI->clone()),
		Folded(other.Folded),
		Name(other.Name),
		Chips(other.Chips),
		BetAmount(other.BetAmount)
	{
		this->HoleCard[0]=other.HoleCard[0];
		this->HoleCard[1]=other.HoleCard[1];
	}

	Player& operator= (const Player& other) {

		//this->AI(other.AI->clone());
		this->Folded = other.Folded;
		this->Name = other.Name;
		this->Chips = other.Chips;
		this->BetAmount = other.BetAmount;

		this->HoleCard[0]=other.HoleCard[0];
		this->HoleCard[1]=other.HoleCard[1];
	
		return *this;
	}
};

#endif
