#include "jout.h"
#include "humanai.h"

ActionTaken HumanAI::getAction(HandState handState) {

	// output current state
	jout << "\n";
	jout << "Hole cards: " <<  handState.holeCard[0] << " ";
	jout <<  handState.holeCard[1] << "\n\n";

	// TODO: add number of remaining players
	jout << "pot: " <<  handState.pot << " current bet:" <<  handState.currentbet;
	jout << "\nposition:" << handState.position << "\n";

	if (handState.cards.size() > 0) {
		for(Card card :  handState.cards) {
			jout << card << " ";
		}
	}

	jout << "\n";

	// can we just check?
	bool canCheck {handState.currentbet == 0};
		
	// get action to take
	bool valid{false};
	char input;

	jout << "You can either [F]old, [C]all (" << handState.currentbet  << ")";

	if (canCheck) {
		jout << ", chec[K] ";
	}
	
	jout <<	", or [R]aise:";

	while(!valid) {
	
		input = getchar();

		// eat endl
		getchar();
		
		if(input=='f' || input=='c' || input=='r' || (canCheck && input=='k')) {
			valid=true;
		}
	}

	// process actions
	ActionTaken result;
	
	switch(input) {
	case 'f':
		result.action=Action::Fold;
		break;
	case 'k':
		result.action=Action::Check;
	case 'c':
		result.action=Action::Call;
		break;
	case 'r':
		result.action=Action::Raise;
	    // todo: currently hardcoded
		result.amount = 200; 
		break;
	}

	return result;
}


