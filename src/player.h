#ifndef Player_H
#define Player_H

#include <string>
#include <vector>
#include <memory>

#include "chips.h"
#include "card.h"
#include "ai.h"

class Player {
public:

	std::unique_ptr<AI> AI;

	bool Folded {false};
	
    std::string Name {""};

	Chips chips;
	
	Card HoleCard[2];

	int BetAmount{0};

	Player(){}

     Player(Player const& other)
		 : AI(other.AI->clone()),
		Folded(other.Folded),
		Name(other.Name),
		chips(other.chips),
		BetAmount(other.BetAmount)
	{
		this->HoleCard[0]=other.HoleCard[0];
		this->HoleCard[1]=other.HoleCard[1];
	}

	Player& operator= (const Player& other) {

		//this->AI(other.AI->clone());
		this->Folded = other.Folded;
		this->Name = other.Name;
		this->chips = other.chips;
		this->BetAmount = other.BetAmount;

		this->HoleCard[0]=other.HoleCard[0];
		this->HoleCard[1]=other.HoleCard[1];
	
		return *this;
	}
};

#endif
