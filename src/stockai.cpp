#include "stockai.h"

ActionTaken StockAI::getAction(int pot, int currentbet, Position position, Card holeCard[], std::vector<Card> cards) {

	ActionTaken result;

	cards.push_back(holeCard[0]);
	cards.push_back(holeCard[1]);

	HandRank hand = Hand(cards).getRanking();

	cout << " " << holeCard[0].ToString() << " " << holeCard[1].ToString();
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



