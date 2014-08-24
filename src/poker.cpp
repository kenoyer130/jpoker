
#include "enums.h"
#include "poker.h"
#include "table.h"
#include "jout.h"

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

	jout << "Starting Game! Good luck!\n";
	
	while(gameState!=GameState::GameEnd) {
		switch(gameState){

		case GameState::HandStart:
			this->cards.clear();
			this->players->nextDealer();
			table->Pot = this->players->ante(this->bigBlind, this->smallBlind);
			startHand();
			
			gameState =  GameState::PreFlop;
			break;
			
		case GameState::PreFlop:
		
			takeActions();

			if(gameState!=GameState::HandEnd) {
				gameState =  GameState::Flop;
			}
			
			break;

		case GameState::Flop:
		
			dealCards(3);

			takeActions();

			if(gameState!=GameState::HandEnd) {
				gameState =  GameState::Turn;
			}

			break;

		case GameState::Turn:
		
			dealCards(1);

			takeActions();

			if(gameState!=GameState::HandEnd) {
				gameState =  GameState::River;
			}

			break;

		case GameState::River:
		
			dealCards(1);

			takeActions();

			break;

		case GameState::HandEnd:
			// remove any players that have no chips
			for (int i = this->players->items.size() -1; i > -1 ; i--) {
				if(this->players->items[i]->Chips < 1) {
					this->players->remove(i);
				}
			}

			// if no more players the game is over!
			if(this->players->items.size() > 1) {
				this->gameState = GameState::HandStart;	
			} else {
				this->gameState = GameState::GameEnd;
			}			
			
			break;
			
	  	case GameState::GameEnd:
			jout << "Game Over!\n";
			break;
		}
	}
}

void Poker::resetPlayers(){
	for(int i = 0;i < this->players->items.size(); i++){

		this->players->items[i]->BetAmount = 0;

		if(this->gameState == GameState::PreFlop){
			this->players->items[i]->Folded = false;
		}
	}
}

void Poker::dealHoleCards() {

	for(int i = 0;i < this->players->items.size(); i++){
		this->players->items[i]->HoleCard[0] = table->DealCard();
		this->players->items[i]->HoleCard[1] = table->DealCard();
	}

	jout << "Starting cards dealt!\n";
}

void Poker::dealCards(int number) {
	for(int j=0; j < number; j++) {
		this->cards.push_back(table->DealCard());
	}
}

void Poker::printState() {

	this->clearScreen();

	jout << GameStateStrings[static_cast<int>(this->gameState)] << "\n";
	
	for(int i = 0; i <  this->players->items.size(); i++) {

		if(this->players->items[i]->Folded) continue;

		jout << "Player: " <<  this->players->items[i]->Name << "\t\t\t";

		jout <<  this->players->items[i]->Chips << "\t";

		jout <<  this->players->items[i]->BetAmount << "\t";
		
		if(i == this->players->Dealer){
			jout << "Dealer ";
		}

		if(i == this->players->SmallBlind){
			jout << "SmallBlind ";
		}
		
		if(i == this->players->BigBlind){
			jout << "BigBlind ";
		}
		
		jout << "\n";
	}
	
	jout << "Pot: " << this->table->Pot << " ";
	jout << "Bet: " << this->currentbet << "\n";
	
	jout << "cards: ";

	for (int i=0; i<this->cards.size(); i++) {
		jout << this->cards[i] << ",";
	}

	jout << "\n";
}

void Poker::startHand() {

	table->ShuffleDeck();

	dealHoleCards();
}

// loop through all active players until no more raises.
void Poker::takeActions() {

	resetPlayers();
	
	this->currentbet = 0;
	
	int startingPlayer {0};
	int currentPlayer {0};

	if(this->gameState == GameState::PreFlop) {

		startingPlayer = this->players->BigBlind;

		// small and big blinds already bet
		this->players->getSmallBlind().BetAmount = this->smallBlind;
		this->players->getBigBlind().BetAmount = this->bigBlind;

		this->currentbet = this->bigBlind;
	
	} else {

		startingPlayer = this->players->Dealer;	
	}

	currentPlayer = this->players->nextPlayerByIndex(startingPlayer);
		
	int raise{0};
	
	while(startingPlayer!=currentPlayer) {

		Player& player = this->players->get(currentPlayer);

		if(player.Folded) {
			currentPlayer = this->players->nextPlayerByIndex(currentPlayer);
			continue;
		}

		jout << "player " << player.Name << " going!" << "\n";

		printState();
	
		HandState handState;
		
		handState.gameState = this->gameState;
		handState.pot = this->table->Pot;
		handState.playerbet = player.BetAmount;
		handState.currentbet = this->currentbet;
		handState.position = this->players->getPosition(player);
		handState.holeCard[0] = player.HoleCard[0];
		handState.holeCard[1] = player.HoleCard[1];
		handState.raise = raise;
		handState.cards = cards;
		
		auto actionTaken = player.AI->getAction(handState);

		switch(actionTaken.action) {
			
		case(Action::Raise):
			jout <<  player.Name << " " << " Raises " << actionTaken.amount << "\n";
			raise++;

			this->table->Pot += actionTaken.amount + this->currentbet;
			this->currentbet += actionTaken.amount;

			player.Chips -= actionTaken.amount;
			player.BetAmount += actionTaken.amount;

			// whenever someone raises we need to go back around.
			startingPlayer = currentPlayer;
			break;
		  
		case(Action::Fold):
			jout <<  player.Name << " " << " Folds.\n";
			player.Folded = true;
			break;

		case(Action::Call):
			jout <<  player.Name << " " << " Calls.\n";

			this->table->Pot += this->currentbet;
			player.Chips -= this->currentbet;
			
			break;

	    case(Action::Check):
			jout <<  player.Name << " " << " Checks.\n";
			break;
		}

		jout << "pause\n";
		getchar();

		// get next player
		currentPlayer = this->players->nextPlayerByIndex(currentPlayer);
	}

	// is our hand over?
	handOver();
 }

void Poker::handOver() {

	vector<int> activePlayers = this->players->activePlayers();

	// if there is only one person left
	if(activePlayers.size() == 1) {
		// mucking is when you win and do not have to show your cards.
		// thus possibly hiding a bluff.
		jout << players->items[activePlayers[0]]->Name << " mucks cards\n";
		playerWon(activePlayers[0]);
		return;
	}

	// if it is the river its showdown time!
	if(this->gameState ==  GameState::River) {

		HandRank highRank;
		int winningPlayer;

		for (int i = 0; i < activePlayers.size(); i++) {
			vector<Card> c {this->cards};

			c.push_back(players->items[activePlayers[i]]->HoleCard[0]);
			c.push_back(players->items[activePlayers[i]]->HoleCard[1]);

			Hand hand(c);
			HandRank handRank = hand.getRanking();

			jout << players->items[activePlayers[i]]->Name << " : " << RankStrings[static_cast<int>(handRank.rank)] << "\n";
			
			if(handRank.rank > highRank.rank) {
				highRank = handRank;
				winningPlayer = i;
			} else if((handRank.rank == highRank.rank)
					  && handRank.card.number > highRank.card.number) {
				highRank = handRank;
				winningPlayer = i;
			}

			//todo deal with ties
		}

		jout << players->items[winningPlayer]->Name << " : " << RankStrings[static_cast<int>(highRank.rank)] << "\n";

		playerWon(activePlayers[winningPlayer]);
	}
}

void Poker::playerWon(int index) {

	jout << this->players->items[index]->Name << " won!\n";
	
	this->gameState = GameState::HandEnd;

	this->players->items[index]->Chips += this->table->Pot;
	
	jout << this->players->items[index]->Name;
	jout << " winnings: " << this->table->Pot;
	jout << " chips: " << this->players->items[index]->Chips << "\n\n";

	getchar();
}

void Poker::clearScreen() {
	int n;
    for (n = 0; n < 10; n++) {
		printf( "\n\n\n\n\n\n\n\n\n\n" );
	}
}
