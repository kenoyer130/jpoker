#ifndef Hand_H
#define Hand_H

#include <algorithm>
#include <vector>

#include "enums.h"
#include "card.h"

using namespace std;

class Hand {

public:

	vector<Card> cards;
	Hand(vector<Card> cards);
	Rank getRanking();

private:

    bool sameSuite();
	bool inOrder();
	bool sameKind();

};

#endif
