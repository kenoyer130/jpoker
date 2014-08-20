#ifndef Hand_H
#define Hand_H

#include <algorithm>
#include <vector>
#include <map>

#include "enums.h"
#include "card.h"

using namespace std;

class Hand {

HandRank getFlush();
HandRank getStraight();
HandRank getSame();
HandRank getPair();

public:

vector<Card> cards;

Hand(vector<Card> cards);

HandRank getRanking();

};

#endif
