#ifndef StockAI_H
#define StockAI_H

#include <iostream>

#include "ai.h"

// standard ai
class StockAI : public AI {
	ActionTaken getAction(int pot, int currentbet, int position, std::vector<Card> cards);
};

#endif
