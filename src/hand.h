// "Copyright 2014 jkenoyer"

#ifndef SRC_HAND_H_
#define SRC_HAND_H_

#include <vector>
#include "./card.h"

using std::vector;

struct HandState {
	GameState gameState;
	int pot{0};
	int currentbet{0};
	int playerbet{0};
	int position;
	Card holeCard[2];
	vector<Card> cards;
	int raise{0};
};

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
