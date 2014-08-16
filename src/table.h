#ifndef Table_H
#define Table_H

#include<vector>

#include "player.h"

class Table {
public:
	double Pot;
	double SmallBlind;
	double BigBlind;

	std::vector<Card> Deck;
	
	std::vector<Player> Players;

	int NumberOfPlayers();

	Player You();

	void ShuffleDeck();

	void AddPlayer(Player player);

	Card DealCard();
	
	void DealHoleCards();

private:
	void seedDeck();
};

#endif
