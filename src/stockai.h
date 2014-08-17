#ifndef StockAI_H
#define StockAI_H

#include <iostream>

#include "ai.h"

// standard ai
class StockAI : public AI {
	ActionTaken getAction(int pot, int currentbet, int position, Card HoleCard[], std::vector<Card> cards);

virtual std::unique_ptr<AI> clone() const
{
	return std::unique_ptr<AI>(new StockAI(*this));
}

};

#endif
