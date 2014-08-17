#ifndef AI_H
#define AI_H

#include <vector>

#include "enums.h"
#include "card.h"

class AI {
	ActionTaken virtual getAction(int pot, int currentbet, int position, std::vector<Card> cards) = 0;
};

#endif
