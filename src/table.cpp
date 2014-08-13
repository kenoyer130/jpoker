#include <iostream>
#include <random>
#include "table.h"

void Table::seedDeck() {
	deck.clear();
	
	for(int i = 0; i < 4;i++) {
		
		for(int c = 0;c<14;c++) {
			Card card;
			card.suite = static_cast<Suite>(i);
			card.number = c;

			deck.push_back(card);
		}
	}
}

void Table::shuffleDeck() {

	std::cout << "shuffling deck!\n";
	
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
	
	for(Card card:deck){
		std::cout << card.ToString() << "\n";
	}
}
