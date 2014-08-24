#include "jout.h"
#include "humanai.h"

ActionTaken HumanAI::getAction(HandState handState) {

	jout << "player bet: " << handState.playerbet << "\n";
	
	// output current state
	jout << "\n";
	jout << "Hole cards: " <<  handState.holeCard[0] << " ";
	jout <<  handState.holeCard[1] << " ";

	handState.cards.push_back(handState.holeCard[0]);
	handState.cards.push_back(handState.holeCard[1]);

	Hand hand(handState.cards);
	HandRank handRank = hand.getRanking();

	jout << "rank: " << RankStrings[static_cast<int>(handRank.rank)] << "\n";

	// get action to take
	bool valid{false};
	char input;

	jout << "You can either [F]old, ";

	if(handState.currentbet != 0) {
		jout << "[C]all";	
	} else {
		jout <<	"[C]heck";
	}	

	jout <<	" (" << handState.currentbet - handState.playerbet << ")";
	
	jout <<	", or [R]aise:";

	while(!valid) {
	
		input = getchar();

		// eat endl
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
		if(handState.currentbet != 0) {
			result.action=Action::Call;
		} else {
			result.action=Action::Check;
		}
		break;
	case 'r':
		result.action=Action::Raise;
	    // todo: currently hardcoded
		result.amount = handState.bigBlind; 
		break;
	}

	return result;
}


