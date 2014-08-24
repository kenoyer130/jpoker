#include <iostream>
#include <assert.h>

#include <random>

#include "deck.h"
#include "jout.h"

void Deck::ShuffleDeck() {

	jout << "shuffling deck!\n";
	
	seedDeck();

	// implements fisher and yates in place shuffle
	std::default_random_engine generator((unsigned int)time(0));

	for(int i = deck.size(); i > -1; i --) {
		std::uniform_int_distribution<int> distribution(0,i);
		int j = distribution(generator); 

		Card temp = deck[j];
		deck[j] = deck[i];
		deck[i] = temp;
	} 
}

// deals one card off the top of the deck
Card Deck::DealCard() {
	Card card = deck.back();
	deck.pop_back();
	return card;
}

void Deck::seedDeck() {
	deck.clear();
	
	for(int i = 0; i < 4;i++) {
		
		for(int c = 1;c < 14;c++) {
			Card card;
			card.suite = static_cast<Suite>(i);
			card.number = c;

			deck.push_back(card);
		}
	}

	// for(Card card:Deck) {
	// 	jout << card << "\n";
	// }
}
