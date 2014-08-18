#include "humanai.h"

ActionTaken HumanAI::getAction(int pot, int currentbet, Position position, Card HoleCard[], std::vector<Card> cards) {

	// output current state
	std::cout << "Hole cards: " <<  HoleCard[0].ToString() << " ";
	std::cout <<  HoleCard[1].ToString() << "\n\n";
	
	std::cout << "pot: " << pot << " current bet:" << currentbet;
	std::cout << " position:" << PositionStrings[static_cast<int>(position)] << "\n";

	for(Card card : cards) {
		std::cout << card.ToString() << " ";
	}

	std::cout << "\n";

	// get action to take
	bool valid;
	char input;

	std::cout << "You can either [F]old, [C]all, or [R]aise:";

	while(!valid) {
	
		input = getchar();
		getchar();
		
		if(input=='f' || input=='c' || input=='r') {
			valid=true;
		}
	}

	// process actions
	ActionTaken result;
	
	switch(input) {
	case 'f':
		result.action=Action::Fold;
		break;
	case 'c':
		result.action=Action::Call;
		break;
	case 'r':
		result.action=Action::Raise;
	    // todo: currently hardcoded
		result.amount = 300; 
		break;
	}

	return result;
}


