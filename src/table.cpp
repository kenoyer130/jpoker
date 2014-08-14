#include <iostream>
#include <random>
#include "table.h"

void Table::AddPlayer(Player player){
	Players.push_back(player);
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
	
	for(Card card:Deck) {
		std::cout << card.ToString() << "\n";
	}
}

void Table::DealHoleCards() {

	for(int i = 0;i < NumberOfPlayers(); i++){
		Players[i].HoleCards[0](DealCard());
		Players[i].HoleCards[1](DealCard());
	}

	std::cout << "Starting cards dealt!\n";
}

Card Table::DealCard() {
	Card card = Deck.front;
	Deck.pop_back();
	return card;
}

int Table::NumberOfPlayers(){
	return Players.size();
}

void Table::seedDeck() {
	Deck.clear();
	
	for(int i = 0; i < 4;i++) {
		
		for(int c = 0;c<14;c++) {
			Card card;
			card.suite = static_cast<Suite>(i);
			card.number = c;

			Deck.push_back(card);
		}
	}
}
