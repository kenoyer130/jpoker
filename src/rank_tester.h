#ifndef RANK_TESTER_H
#define RANK_TESTER_H

#include <iostream>

#include "enums.h"
#include "hand.h"

using namespace std;

class RankTester {

public:
	void Run();
	void Assert(string test, vector<Card> cards, Rank rank, int highCard);
	void shuffle(vector<Card>& cards);
	
};


#endif /* RANK_TESTER_H */
