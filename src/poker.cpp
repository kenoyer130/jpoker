#include <iostream>

#include "enums.h"
#include "poker.h"
#include "table.h"

Poker::Poker() {
	// load config
	Configurator configurator;
	Configuration config = configurator.Get();
	
	this->bigBlind = config.BigBlind;
	this->smallBlind = config.SmallBlind;
	
	// set players
	auto players = std::unique_ptr<Players>(new Players(config));
	this->players = std::move(players);

	// set table
	auto table = std::unique_ptr<Table>(new Table(config));
	this->table = std::move(table);
}

void Poker::StartGame() {

	gameState = GameState::HandStart;

	std::cout << "Starting Game! Good luck!\n";
	
	while(gameState!=GameState::GameEnd) {
		switch(gameState){

		case GameState::HandStart:
			clearPlayers();
			this->players->nextDealer();
			table->Pot += this->players->ante(this->bigBlind, this->smallBlind);
			printState();
			startHand();
			break;

		case GameState::GameEnd:
			break;
		}
	}

    std::cout << "Game Over!\n";
}

void Poker::clearPlayers(){
	for(int i = 0;i < this->players->items.size(); i++){
		this->players->items[i]->BetAmount = 0;
	}
}

void Poker::dealHoleCards() {

	for(int i = 0;i < this->players->items.size(); i++){
		this->players->items[i]->HoleCard[0] = table->DealCard();
		this->players->items[i]->HoleCard[1] = table->DealCard();
	}

	std::cout << "Starting cards dealt!\n";
}


void Poker::printState() {

	std::cout << "\n";
	std::cout << "Pot: " << this->table->Pot << "\n";
	std::cout << "\n";
	
	for(int i = 0; i <  this->players->items.size(); i++) {
		std::cout << "Player: " <<  this->players->items[i]->Name << "\t\t";

		std::cout <<  this->players->items[i]->Chips << "\t";

		std::cout <<  this->players->items[i]->BetAmount << "\t";
		
		if(this->players->items[i]->Dealer){
			std::cout << "Dealer ";
		}

		if(this->players->items[i]->BigBlind){
			std::cout << "BigBlind ";
		}

		if(this->players->items[i]->SmallBlind){
			std::cout << "LittleBlind ";
		}
		
		std::cout << "\n";
	}

	std::cout << "\n";
}

void Poker::startHand() {

	table->ShuffleDeck();

	dealHoleCards();
			
	std::cout << "Your hole cards: " <<  this->players->You().HoleCard[0].ToString() << " ";
	std::cout <<  this->players->You().HoleCard[1].ToString() << "\n\n";
			
	gameState = GameState::GameEnd;
}
