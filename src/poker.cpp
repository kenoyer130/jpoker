
#include "enums.h"
#include "poker.h"
#include "deck.h"
#include "jout.h"

#include <algorithm>

using std::remove_if;

Poker::Poker() {

    // load config
	Configurator configurator;
	Configuration config = configurator.Get();
	
	this->bigBlind = config.BigBlind;
	this->smallBlind = config.SmallBlind;
	this->handBlinds = config.HandBlinds;
	
	// set players
	auto players = unique_ptr<Players>(new Players(config));
	this->players = move(players);
}

void Poker::StartGame() {

	gameState = GameState::HandStart;

	jout << "Starting Game! Good luck!\n";
	
	while(gameState!=GameState::GameEnd) {
		switch(gameState){

		case GameState::HandStart:
			this->cards.clear();
			this->players->nextDealer();
			this->Pot = this->players->ante(this->bigBlind, this->smallBlind);
			startHand();
			
			gameState = GameState::PreFlop;
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

			if(gameState != GameState::HandEnd) {
				gameState = GameState::Turn;
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

		case GameState::HandEnd: {

			this->handCount++;

			// time to raise blinds?
			if(this->handCount == this->handBlinds) {
				this->handCount = 0;
				this->smallBlind *= 2;
				this->bigBlind *= 2;
			}

			// remove any players that have no chips
			this->players->items.erase(std::remove_if(this->players->items.begin(), this->players->items.end(), [](unique_ptr<Player> const& player)
													 {														 
														 return player->chips.get() <= 0;
													 }), this->players->items.end());
			
			// if no more players the game is over!
			if(this->players->items.size() > 1) {
				this->gameState = GameState::HandStart;	
			} else {
				this->gameState = GameState::GameEnd;
			}			
			
			break;
		}
			
	  	case GameState::GameEnd: {
			// will be handled when loop exits
			break;
		   }
		}
	}

	jout << "Game over!\n" << this->players->items[0]->
		Name << " Won the tournament!\n\n";
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
		this->players->items[i]->HoleCard[0] = deck.DealCard();
		this->players->items[i]->HoleCard[1] = deck.DealCard();
	}

	jout << "Starting cards dealt!\n";
}

void Poker::dealCards(int number) {
	for(int j=0; j < number; j++) {
		this->cards.push_back(deck.DealCard());
	}
}

void Poker::printState() {

	this->clearScreen();

	jout << GameStateStrings[static_cast<int>(this->gameState)] << "\n";
	
	for(int i = 0; i <  this->players->items.size(); i++) {

		if(this->players->items[i]->Folded) continue;

		jout << "Player: " <<  this->players->items[i]->Name << "\t\t\t";

		jout <<  this->players->items[i]->chips.get() << "\t";

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
	
	jout << "Pot: " << this->Pot << " ";
	jout << "Bet: " << this->currentbet << "\n";
	
	jout << "cards: ";

	for (int i=0; i<this->cards.size(); i++) {
		jout << this->cards[i] << ",";
	}

	jout << "\n";
}

void Poker::startHand() {

	deck.ShuffleDeck();

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

	    currentPlayer = this->players->nextPlayerByIndex(startingPlayer);
	} else {
		startingPlayer = this->players->nextPlayerByIndex(this->players->Dealer);
		currentPlayer = startingPlayer;
	}
		
	int raise {0};
	int checks {0};
	
	do {

		Player& player = this->players->get(currentPlayer);

		if(player.Folded) {
			currentPlayer = this->players->nextPlayerByIndex(currentPlayer);
			continue;
		}

		if(player.chips.get() == 0) {
			jout << player.Name << " is ALL IN!\n";
			currentPlayer = this->players->nextPlayerByIndex(currentPlayer);
			continue;
		}

		jout << "player " << player.Name << " going!" << "\n";

		printState();
	
		HandState handState;
		
		handState.gameState = this->gameState;
		handState.pot = this->Pot;
		handState.playerbet = player.BetAmount;
		handState.currentbet = this->currentbet;
		handState.position = this->players->getPosition(player);
		handState.holeCard[0] = player.HoleCard[0];
		handState.holeCard[1] = player.HoleCard[1];
		handState.raise = raise;
		handState.cards = cards;
		handState.checks = checks;
		handState.chips = player.chips.get();
		handState.bigBlind = this->bigBlind;

		
		auto actionTaken = player.AI->getAction(handState);
		
		switch(actionTaken.action) {
			// note the use of {} to limit scope	
		case(Action::Raise): {

			raise++;

			int amount = player.chips.bet(actionTaken.amount);
						
			this->Pot += amount + this->currentbet;
			this->currentbet += amount;

			player.BetAmount += amount;

			jout <<  player.Name << " " << " Raises " << amount << "\n";
			
			checks = 0;
			
			// whenever someone raises we need to go back around.
			startingPlayer = currentPlayer;
			break;
		}
		  
		case(Action::Fold):
			jout <<  player.Name << " " << " Folds.\n";
			player.Folded = true;
			break;

		case(Action::Call): {
			jout <<  player.Name << " " << " Calls.\n";

			int currentbet = player.chips.bet(this->currentbet);
			
			this->Pot += currentbet;
			
			break;
		}
			
	    case(Action::Check): {
			 jout <<  player.Name << " " << " Checks.\n";
			 checks++;
			 break;
		   }
		}

		jout << "pause\n";
		getchar();

		// get next player
		currentPlayer = this->players->nextPlayerByIndex(currentPlayer);
		
	} while(startingPlayer != currentPlayer);

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
	if(this->gameState == GameState::River) {

		HandRank highRank;
		int winningPlayer;

		for (int i = 0; i < activePlayers.size(); i++) {
			vector<Card> c {this->cards};

			c.push_back(players->items[activePlayers[i]]->HoleCard[0]);
			c.push_back(players->items[activePlayers[i]]->HoleCard[1]);

			Hand hand(c);
			HandRank handRank = hand.getRanking();

			jout << players->items[activePlayers[i]]->Name << " " << handRank << " " << hand << "\n"; 
			
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
		
	jout << "winner: " << this->players->items[index]->Name << "\n";

	if(this->players->items[index]->chips.get() == 0) {
		jout << "WAS ALL IN!!\n";
	}

	this->players->items[index]->chips.add(this->Pot);

	jout << " winnings: " << this->Pot;
	jout << " chips: " << this->players->items[index]->chips.get() << "\n\n";

	getchar();
}

void Poker::clearScreen() {
	int n;
    for (n = 0; n < 10; n++) {
		printf( "\n\n\n\n\n\n\n\n\n\n" );
	}
}
