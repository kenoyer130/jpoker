#ifndef Enums_H
#define Enums_H

#include <string>

enum class GameState {
	HandStart,
	PreFlop,
	GameEnd
};

enum class Suite {
	HEART=0,
	SPADE=1,
	CLOVER=2,
	DIAMOND=3
};

static const std::string SuiteStrings[] = { "Hearts", "Spades", "Clubs", "Diamonds" };	

enum class Action {
	Fold,
	Call,
	Raise
};

struct ActionTaken {
	Action action;
	int amount;
};

#endif

