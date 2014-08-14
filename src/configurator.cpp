#include "configurator.h"
#include "player.h"

//todo: read from config file
void Configurator::Load(Table* table){

	table->SmallBlind = 100;
	table->BigBlind = 200;
	
	int numberOfPlayers =  6;
	
	std::string names[5]{"Jim", "Bob","Joe","Slacker","Bot5000"};
	
	int startChips = 2000;

	for(int i=0;i < numberOfPlayers - 1; i++){
		Player player;
		player.Chips = startChips;
		player.Name = names[i];
	    
		table->Players.push_back(player);
	}

	// last player is human
	Player human;
	human.Chips = startChips;
	human.Name = "You";
    
	table->Players.push_back(human);
	table->You = &human;
}
