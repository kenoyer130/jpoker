#ifndef Deck_H
#define Deck_H

#include <vector>
#include <memory>

#include "player.h"
#include "players.h"
#include "configurator.h"

class Deck {
public:

	std::vector<Card> deck;
	
	void ShuffleDeck();

	Card DealCard();
	
	void DealHoleCards();

private:
	
	void seedDeck();
};

#endif
