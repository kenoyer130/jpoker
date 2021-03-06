#ifndef SRC_HAND_H_
#define SRC_HAND_H_

#include <vector>
#include "./card.h"
#include "./hand_rank.h"

using std::vector;

struct HandState {
	GameState gameState;
	int pot {0};
	int currentbet {0};
	int playerbet {0};
	int position {0};
	Card holeCard[2];
	vector<Card> cards;
	int raise {0};
	int checks {0};
	int chips {0};
	int bigBlind {0};
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

	friend ostream& operator<<(ostream& os, const Hand& hand);
};

#endif  // SRC_HAND_H_
