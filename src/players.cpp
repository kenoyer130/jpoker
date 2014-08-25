#include <assert.h>

#include "configurator.h"
#include "players.h"
#include "humanai.h"
#include "stockai.h"

// constructor

Players::Players(Configuration config) {

	if(!config.AutoMode) {
		// first player is human for faster lookup.
		std::unique_ptr<Player> human(new Player());

		human->chips.set(config.StartingChips);
		human->Name = "You";

		std::unique_ptr<HumanAI> human_ai(new HumanAI());
		human->AI = std::move(human_ai);
	
		this->items.push_back(std::move(human));
	}
	
	// seed other players
	for(int i=0;i < config.PlayerNames.size(); i++){

		std::unique_ptr<Player> player(new Player());
		player->chips.set(config.StartingChips);
		player->Name = config.PlayerNames[i];

		std::unique_ptr<StockAI> stock_ai(new StockAI());
		player->AI = std::move(stock_ai);
	
		this->items.push_back(std::move(player));
	}

	// set dealer
	std::default_random_engine generator(std::random_device{}());
	std::uniform_int_distribution<int> distribution(0, this->items.size()-1);
	int startingDealer = distribution(generator);

	// we set the dealer then iterator one to also properly seed the big and small blinds.
	this->Dealer = startingDealer;
	nextDealer();
}

Player& Players::getDealer() {
	return *this->items[this->Dealer];
}	

Player& Players::getBigBlind() {
	return *this->items[this->BigBlind];
}	

Player& Players::getSmallBlind() {
	return *this->items[this->SmallBlind];
}	

// moves the dealer button to the next player on the left
// also resets the big and little blinds.
void Players::nextDealer() {
	
	// if the previous dealer was removed set it to the first player
	if(this->Dealer > (this->items.size() -1)) {
		this->Dealer = 0;
	}

    // set next dealer
	this->Dealer = next(get(this->Dealer));
	
	// set the blinds
	this->SmallBlind = next(get(this->Dealer));
	this->BigBlind = next(get(this->SmallBlind));
}

// returns the combined ante of the small and big blind.
// also decrements the big and small blind players chips.
int Players::ante(int bigBlind, int smallBlind) {
	
	int bigante = this->items[this->BigBlind]->chips.bet(bigBlind);
	int smallante = this->items[this->SmallBlind]->chips.bet(smallBlind);

	return bigante + smallante;
}

// Returns an index of the player to the "left" of indicated player.
// Handles wrapping so if the player is the last player will return 0;
int Players::next(const Player& player) {
	// find matching player
	for(int i=0;i<this->items.size(); i++) {
		
		if(player.Name==this->items[i]->Name) {
		    return nextPlayerByIndex(i);
		}
	}

	assert(0);
}

int Players::nextPlayerByIndex(int index) {
	if(index != this->items.size()-1) {
		return index+1;
	} else {
		return 0;
	}  
}

// returns a reference to the player at the indicated index.
Player& Players::get(int index) {
	return *this->items[index].get();
}

// returns a reference to the next player from the provided player.
// call this if you intend to modify the next player.
Player& Players::getNext(const Player& player) {
	int index = this->next(player);
	return this->get(index);
}

// figures out the players position in relation to the dealer.
int Players::getPosition(const Player& player) {

    // if dealer return special
	if(get(this->Dealer).Name == player.Name) {
		return -1;
	}
	
	// walk through and find out how far we are from the dealer.
	int position(0);
	bool found(false);

	int index = this->Dealer;

	// loop around until we find the dealer
	while(!found) {
		Player& current = this->get(index);
		if(current.Name == player.Name){
			found = true;
		} else {
			position++;
			index = this->next(current);
		}
	}
	
	return (this->items.size() - position);
}

vector<int> Players::activePlayers() {

	vector<int> active;
	
	for (int i = 0; i < this->items.size(); i++) {
		if(!this->items[i]->Folded) {
			active.push_back(i);
		}
	}

	return active;
}

// removes player
void Players::remove(int index) {

	Player& loser = this->get(index);

	jout << loser.Name << " has left the table.\n";
	
	this->items.erase(this->items.begin() +  index);
}

