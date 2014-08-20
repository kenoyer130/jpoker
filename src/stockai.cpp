#include "stockai.h"

ActionTaken StockAI::getAction(HandState handState) {

	ActionTaken result;

	handState.cards.push_back(handState.holeCard[0]);
	handState.cards.push_back(handState.holeCard[1]);

	HandRank hand = Hand(handState.cards).getRanking();

	cout << " " << handState.holeCard[0].ToString() << " " <<  handState.holeCard[1].ToString();
	cout << RankStrings[static_cast<int>(hand.rank)] << "\n";
	
	// if none is found we got crap so fold
	if(hand.rank == Rank::Nothing) {
		result.action = Action::Fold;
		return result;
	}
	
	if(hand.rank > Rank::ThreeKind) {
		result.action=Action::Raise;
		// todo: currently hardcoded
		result.amount = 300;
	} else {
		result.action=Action::Call;
	} 

	return result;
}



