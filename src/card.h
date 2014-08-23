#ifndef Card_H
#define Card_H

#include <string>
#include <sstream>
#include <iostream>

#include "enums.h"
#include "jout.h"

using std::ostream;

class Card {
	
public:
	
    int number;
	Suite suite;

	// constructors
	Card();
	Card(int number, Suite suite);

	// sorter
	bool operator<(const Card &rhs) const { return number < rhs.number; }

    friend ostream& operator<<(ostream& os, const Card& c);
};

// represents a certain hand ranking and the highest card.
// for example a Rank of ThreeKind and Card.number=5 would be
// 3 fives. A Rank of Flush with Card.number=9 means a flush 10 high.
 class HandRank {

public:
	Rank rank;
	Card card;

HandRank(): rank(Rank::Nothing) {
		
	}
};

#endif
