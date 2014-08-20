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
	CLUBS=2,
	DIAMOND=4
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
	"Early",
	"Middle",
    "Late",
	"Dealer"
};

enum class Position {
	Early,
	Middle,
		Late,
		Dealer
};

static const std::string RankStrings[] = {
	"Nothing",
	"HighCard",
	"OnePair",
	"TwoPair",
	"ThreeKind",
	"Straight",
	"Flush",
	"FullHouse",
	"FourKind",
   	"StraightFlush"
};

enum class Rank {
	Nothing,
	HighCard,
	OnePair,
	TwoPair,
	ThreeKind,
	Straight,
	Flush,
	FullHouse,
	FourKind,
   	StraightFlush
};

#endif

