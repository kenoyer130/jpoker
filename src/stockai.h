#ifndef StockAI_H
#define StockAI_H

#include <iostream>

#include "ai.h"
#include "bettables.h"

// standard ai
class StockAI : public AI {

	BetTables tables;
	
	ActionTaken getAction(int pot, int currentbet, Position position, Card HoleCard[], std::vector<Card> cards);

	virtual std::unique_ptr<AI> clone() const
	{
		return std::unique_ptr<AI>(new StockAI(*this));
	}
};

#endif
