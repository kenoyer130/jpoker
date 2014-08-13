#include <iostream>
#include "table.h"

void Table::shuffleDeck() {
	deck.clear();

	std::cout << "shuffling deck!\n";
	
	for(int i = 0; i < 4;i++) {
		
		for(int c = 0;c<14;c++) {
			Card card;
			card.suite = static_cast<Suite>(i);
			card.number = c;

			deck.push_back(card);
		}
	}

	for(Card card:deck){
		std::cout << card.ToString() << "\n";
	}
}
