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
			resetPlayers();
			this->players->nextDealer();
			table->Pot += this->players->ante(this->bigBlind, this->smallBlind);
			printState();
			startHand();
			gameState =  GameState::PreFlop;
			break;
			
		case GameState::PreFlop:
			takeActions();
			gameState = GameState::GameEnd;
			break;
			
	  	case GameState::GameEnd:
			break;
		}
	}

    std::cout << "Game Over!\n";
}

void Poker::resetPlayers(){
	for(int i = 0;i < this->players->items.size(); i++){
		this->players->items[i]->BetAmount = 0;
		this->players->items[i]->Folded = false;
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
}

void Poker::startHand() {

	table->ShuffleDeck();

	dealHoleCards();
}

void Poker::takeActions() {
	for(int i = 0;i < this->players->items.size(); i++){

 		Player& player = *this->players->items[i].get();
		
		if(player.Folded) {
			continue;
		}
		
		// todo: returns max int?
		int position = this->players->getPosition(player);

		auto actionTaken = player.AI->getAction(this->table->Pot, this->currentbet, position, player.HoleCard, cards);

		switch(actionTaken.action) {
			
		case(Action::Raise):
		 	this->table->Pot += actionTaken.amount;
			this->currentbet += actionTaken.amount;
			player.Chips -= actionTaken.amount;
			break;
		  
		case(Action::Fold):
			player.Folded = true;
			break;

		case(Action::Call):
			break;
		}
	}
}
