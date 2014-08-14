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

	Player* You;
	
	std::vector<Player> Players;

	int NumberOfPlayers();

	void ShuffleDeck();

	void AddPlayer(Player player);

	void DealCard();
	
	void DealHoleCards();

private:
	void seedDeck();
};

#endif
