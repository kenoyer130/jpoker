#ifndef HAND_RANK_H
#define HAND_RANK_H

#include "./enums.h"
#include "./card.h"

// represents a certain hand ranking and the highest card.
// for example a Rank of ThreeKind and Card.number=5 would be
// 3 fives. A Rank of Flush with Card.number=9 means a flush 10 high.
class HandRank {

public:

	Rank rank;
	Card card;

    HandRank(): rank(Rank::Nothing) {
		
	}

    friend ostream& operator<<(ostream& os, const HandRank& handRank);
};

#endif /* HAND_RANK_H */
