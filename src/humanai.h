#ifndef HumanAI_H
#define HumanAI_H

#include <iostream>

#include "ai.h"

// represents an AI that asks for human input
class HumanAI : public AI {
	ActionTaken getAction(int pot, int currentbet, int position, std::vector<Card> cards);
};

#endif
