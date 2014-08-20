#ifndef AI_H
#define AI_H

#include <vector>
#include <memory>

#include "enums.h"
#include "card.h"
#include "hand.h"

class AI {

public:

	ActionTaken virtual getAction(HandState handState) = 0;
	virtual std::unique_ptr<AI> clone() const = 0; 
	
};

#endif
