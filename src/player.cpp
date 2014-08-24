#include "player.h"

int Player::bet(int amount) {
	if(this->Chips - amount < 1) {
		int actualBet = this->Chips;
		this->Chips = 0;
		this->BetAmount += actualBet;
		return actualBet;
	}

	this->Chips -= amount;
	this->BetAmount += amount;

	return amount;
}

