#ifndef StockAI_H
#define StockAI_H

#include <iostream>

#include "ai.h"
#include "hand.h"

using std::cout;

// standard ai
class StockAI : public AI {

public:
	
	ActionTaken getAction(HandState handState);

	int getPreFlopDecision(HandRank rank, HandState handState);
	
	virtual std::unique_ptr<AI> clone() const
	{
		return std::unique_ptr<AI>(new StockAI(*this));
	}
};

#endif
