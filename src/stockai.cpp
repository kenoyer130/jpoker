#include "stockai.h"

ActionTaken StockAI::getAction(int pot, int currentbet, int position, std::vector<Card> cards) {
	
	ActionTaken result;

	result.action=Action::Raise;
    // todo: currently hardcoded
	result.amount = 300; 

	return result;
}
