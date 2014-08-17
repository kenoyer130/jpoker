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

	Player(){}

     Player(Player const& other)
		 : AI(other.AI->clone()),
		Dealer(other.Dealer),
		BigBlind(other.BigBlind),
		SmallBlind(other.SmallBlind),
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
		this->Dealer = other.Dealer;
		this->BigBlind = other.BigBlind;
		this->SmallBlind = other.SmallBlind;
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
