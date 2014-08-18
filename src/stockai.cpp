#include "stockai.h"

ActionTaken StockAI::getAction(int pot, int currentbet, Position position, Card holeCard[], std::vector<Card> cards) {

	ActionTaken result;

	// get percent chance for our two hole cards
	HoleCards holeCards(holeCard[0].number, holeCard[1].number);

	// if none is found we got crap so fold
	if(this->tables.HoleCards.find(holeCards.key()) == (this->tables.HoleCards.end())) {
		result.action = Action::Fold;
		return result;
	}
	
	// modify by position
	int percent = this->tables.HoleCards[holeCards.key()];

	// if same suite knock up a rank
	if(holeCard[0].suite==holeCard[1].suite){
		percent = percent + 10;
	}
	
	// roll to see if we are calling
		
	if(percent > 100) {
		result.action=Action::Raise;
		// todo: currently hardcoded
		result.amount = 300;
	} else if(percent > 80) {
		result.action=Action::Call;
	} else {
		result.action = Action::Fold;
	}

	return result;
}



