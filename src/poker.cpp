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
	auto players = unique_ptr<Players>(new Players(config));
	this->players = move(players);

	// set table
	auto table = unique_ptr<Table>(new Table(config));
	this->table = move(table);
}

void Poker::StartGame() {

	gameState = GameState::HandStart;

	cout << "Starting Game! Good luck!\n";
	
	while(gameState!=GameState::GameEnd) {
		switch(gameState){

		case GameState::HandStart:
			resetPlayers();
			this->players->nextDealer();
			table->Pot += this->players->ante(this->bigBlind, this->smallBlind);
			printState();
			startHand();
			this->currentbet = this->bigBlind;
			gameState =  GameState::PreFlop;
			break;
			
		case GameState::PreFlop:
			takeActions();
			gameState = GameState::GameEnd;
			break;
			
	  	case GameState::GameEnd:
			cout << "Game Over!\n";
			break;
		}
	}
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

	cout << "Starting cards dealt!\n";
}

void Poker::printState() {

	cout << "\n";
	cout << "Pot: " << this->table->Pot << "\n";
	cout << "\n";
	
	for(int i = 0; i <  this->players->items.size(); i++) {
		cout << "Player: " <<  this->players->items[i]->Name << "\t\t\t";

		cout <<  this->players->items[i]->Chips << "\t";

		cout <<  this->players->items[i]->BetAmount << "\t";
		
		if(i == this->players->Dealer){
			cout << "Dealer ";
		}

		if(i == this->players->SmallBlind){
			cout << "SmallBlind ";
		}

		if(i == this->players->BigBlind){
			cout << "BigBlind ";
		}
		
		cout << "\n";
	}
}

void Poker::startHand() {

	table->ShuffleDeck();

	dealHoleCards();
}

// loop through all active players until no more raises.
void Poker::takeActions() {

	cout << "starting betting round!\n";

	// betting always starts to the left of the big blind.
	// betting continues until play returns to the starting player.
	// note if someone raises they then become the starting player to give all players the chance to call or fold.
	int startingPlayer = this->players->BigBlind;
	int currentPlayer = this->players->nextPlayerByIndex(startingPlayer); 

	while(startingPlayer!=currentPlayer) {

		Player& player = this->players->get(currentPlayer);

		if(player.Folded) {
			continue;
		}

		cout << "player " << player.Name << " going!" << endl;		
		
		Position position = this->players->getPosition(player);

		auto actionTaken = player.AI->getAction(this->table->Pot, this->currentbet, position, player.HoleCard, cards);

		switch(actionTaken.action) {
			
		case(Action::Raise):
			cout <<  player.Name << " " << " Raises " << actionTaken.amount << "\n";
			this->table->Pot += actionTaken.amount;
			this->currentbet += actionTaken.amount;
			player.Chips -= actionTaken.amount;
			break;
		  
		case(Action::Fold):
			cout <<  player.Name << " " << " Folds.\n";
			player.Folded = true;
			break;

		case(Action::Call):
			cout <<  player.Name << " " << " Calls.\n";
			break;
		}

		// get next player
		currentPlayer = this->players->nextPlayerByIndex(currentPlayer);
	}
 }
