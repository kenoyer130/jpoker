#ifndef AI_H
#define AI_H

#include <vector>
#include <memory>

#include "enums.h"
#include "card.h"

class AI {

public:

	ActionTaken virtual getAction(int pot, int currentbet, Position position, Card holeCards[], std::vector<Card> cards) = 0;

	virtual std::unique_ptr<AI> clone() const = 0; 
	
};

#endif
