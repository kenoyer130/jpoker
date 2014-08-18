#ifndef BetTables_H
#define BetTables_H

#include <map>
#include <string>

#include "enums.h"

using namespace std;

// class used to generate unique keys for holecards
// ignores the actual suites
class HoleCards {

public:
	int card1;
	int card2;

	HoleCards(int card1, int card2) {
		this->card1 = card1;
		this->card2 = card2;
	}

	// uses Cantor pairing function
	int key() {
		return (this->card1 + this->card2) * (this->card1 + this->card2 + 1) / 2 + this->card1;
	}
};

// represents ranking of hands used by AI.
class BetTables {
public:
	map<int, int> HoleCards;
	void seedHoleCards();
};

#endif
