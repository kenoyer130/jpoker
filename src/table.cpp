#include <iostream>
#include <assert.h>

#include <random>
#include "table.h"

Table::Table(Configuration config) {
	this->config = config;
}

void Table::ShuffleDeck() {

	std::cout << "shuffling deck!\n";
	
	seedDeck();

	// implements fisher and yates in place shuffle
	std::default_random_engine generator((unsigned int)time(0));

	for(int i = Deck.size(); i > -1; i --) {
		std::uniform_int_distribution<int> distribution(0,i);
		int j = distribution(generator); 

		Card temp = Deck[j];
		Deck[j] = Deck[i];
		Deck[i] = temp;
	} 
}

// deals one card off the top of the deck
Card Table::DealCard() {
	Card card = Deck.back();
	Deck.pop_back();
	return card;
}

void Table::seedDeck() {
	Deck.clear();
	
	for(int i = 0; i < 4;i++) {
		
		for(int c = 0;c < 13;c++) {
			Card card;
			card.suite = static_cast<Suite>(i);
			card.number = c;

			Deck.push_back(card);
		}
	}

	//for(Card card:Deck) {
	//	std::cout << card.ToString() << "\n";
	// }
}
