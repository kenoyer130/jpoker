#ifndef HumanAI_H
#define HumanAI_H

#include <iostream>

#include "ai.h"

// represents an AI that asks for human input
class HumanAI : public AI {

ActionTaken getAction(int pot, int currentbet, int position, Card holeCard[2], std::vector<Card> cards);

virtual std::unique_ptr<AI> clone() const
{
	return std::unique_ptr<AI>(new HumanAI(*this));
}

};


#endif
