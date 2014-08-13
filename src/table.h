#ifndef Table_H
#define Table_H

#include<vector>

#include "player.h"

class Table {
public:
	double pot;
	double blind;
	std::vector<Card> deck;

	Player* dealer;
	
	std::vector<Player> players;

	void shuffleDeck();

private:
	void seedDeck();
};

#endif
