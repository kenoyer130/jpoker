#include <assert.h>

#include "configurator.h"
#include "players.h"

// constructor
Players::Players(Configuration config) {
	
	// first player is human for faster lookup.
	std::unique_ptr<Player> human(new Player());

	human->Chips = config.StartingChips;
	human->Name = "You";
	human->AI = false;
	
	this->items.push_back(std::move(human));

	// seed other players
	for(int i=0;i < config.PlayerNames.size(); i++){

		std::unique_ptr<Player> player(new Player());
		player->Chips = config.StartingChips;
		player->Name = config.PlayerNames[i];
		player->AI = true;
		
		this->items.push_back(std::move(player));
	}

	// set dealer
	std::default_random_engine generator((unsigned int)time(0));

	std::uniform_int_distribution<int> distribution(0, this->items.size()-1);
	int startingDealer = distribution(generator);

	// we set the dealer then iterator one to also properly seed the big and small blinds.
	this->items[startingDealer]->Dealer = true;
	nextDealer();
}

// returns a reference to the player that is you!
Player& Players::You() {
	for(int i = 0; i < this->items.size() -1; i++) {
		if(!this->items[i]-> AI) return *this->items[i].get();
	}

	assert(0);
}

Player& Players::Dealer() {
	for(int i = 0; i < this->items.size() -1; i++) {
		if(this->items[i]-> Dealer) return *this->items[i].get();
	}

	assert(0);
}	

void Players::clearDealer() {
	for(int i = 0; i < this->items.size() -1; i++) {
		this->items[i]-> Dealer = false;
	}
}

void Players::clearBlinds() {
	for(int i = 0; i < this->items.size() -1; i++) {
		this->items[i]->SmallBlind = false;
		this->items[i]->BigBlind = false;
	}
}


Player& Players::BigBlind() {
	for(int i = 0; i < this->items.size() -1; i++) {
		if(this->items[i]-> BigBlind) return *this->items[i].get();
	}

	assert(0);
}	

Player& Players::SmallBlind() {
	for(int i = 0; i < this->items.size() -1; i++) {
		if(this->items[i]-> SmallBlind) return *this->items[i].get();
	}

	assert(0);
}	

// moves the dealer button to the next player on the left
// also resets the big and little blinds.
void Players::nextDealer() {
	// clear current
	auto oldDealer = this->Dealer();
	oldDealer.Dealer = false;
		
	this->clearBlinds();

	// set next dealer
	auto nextDealer = next(oldDealer);
	nextDealer.Dealer=true;
	
	// set the blinds
	next(nextDealer).BigBlind=true;
	next(this->BigBlind()).SmallBlind=true;
}

// Returns the next player to the left of indicated player.
// handles wrapping.
Player& Players::next(const Player& player) {
   // find matching player
	for(int i=0;i<this->items.size() -1; i++) {
		
		if(player.Name==this->items[i]->Name) {
			// once found get the next entry or the first entry if at end
			if(i!=this->items.size()-1) {
				return *this->items[i+1].get();
			} else {
				return *this->items[0].get();
			}
		}
	}

	assert(0);
}

// removes player
void Players::remove(Player& player) {
	
}

