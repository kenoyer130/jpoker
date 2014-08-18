#ifndef HumanAI_H
#define HumanAI_H

#include <iostream>

#include "ai.h"

using namespace std;

// represents an AI that asks for human input
class HumanAI : public AI {

ActionTaken getAction(int pot, int currentbet, Position position, Card holeCard[2], vector<Card> cards);

virtual unique_ptr<AI> clone() const
{
	return unique_ptr<AI>(new HumanAI(*this));
}

};


#endif
