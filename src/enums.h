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

static const std::string PositionStrings[] = {
	"Dealer",
	"SmallBlind",
    "BigBlind",
	"UnderTheGun",
	"Position1",
	"Position2",
	"Position3",
	"Position4",
	"Position5"
};

enum class Position {
	Dealer=8,
	SmallBlind=0,
	BigBlind=1,
	UnderTheGun=2,
	Position1=3,
	Position2=4,
	Position3=5,
	Position4=6,
	Position5=7
};

#endif

