#ifndef Table_H
#define Table_H

#include <vector>
#include <memory>

#include "player.h"
#include "players.h"
#include "configurator.h"

class Table {
public:

	double Pot;
	
	std::vector<Card> Deck;
	
	Table(Configuration config);

	void ShuffleDeck();

	Card DealCard();
	
	void DealHoleCards();

private:
	Configuration config;
	void seedDeck();
};

#endif
