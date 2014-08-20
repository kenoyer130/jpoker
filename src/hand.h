// "Copyright 2014 jkenoyer"

#ifndef SRC_HAND_H_
#define SRC_HAND_H_

#include <vector>
#include "./card.h"

using std::vector;

class Hand {
    HandRank getFlush();
    HandRank getStraight();
    HandRank getSame();
    HandRank getPair();

 public:
    vector<Card> cards;
    explicit Hand(vector<Card> cards);
    HandRank getRanking();
};

#endif  // SRC_HAND_H_
