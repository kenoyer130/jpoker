#include "humanai.h"

ActionTaken HumanAI::getAction(HandState handState) {

	// output current state
	cout << "\n";
	std::cout << "Hole cards: " <<  handState.holeCard[0].ToString() << " ";
	std::cout <<  handState.holeCard[1].ToString() << "\n\n";

	// TODO: add number of remaining players
	std::cout << "pot: " <<  handState.pot << " current bet:" <<  handState.currentbet;
	std::cout << " position:" << PositionStrings[static_cast<int>( handState.position)] << "\n";

	if (handState.cards.size() > 0) {
		for(Card card :  handState.cards) {
			std::cout << card.ToString() << " ";
		}
	}

	std::cout << "\n";

	// get action to take
	bool valid{false};
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


