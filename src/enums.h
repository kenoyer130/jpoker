#ifndef Enums_H
#define Enums_H

#include <string>

enum class GameState {
	HandStart,
	PreFlop,
    Flop,
	Turn,
	River,
	HandEnd,
	GameEnd
};

static const std::string GameStateStrings[] = {
	"HandStart", "PreFlop", "Flop", "Turn", "River", "HandEnd", "GameEnd"
};	

enum class Suite {
	HEART,
	SPADE,
	CLUBS,
	DIAMOND
};

static const std::string SuiteStrings[] = { "H", "S", "C", "D" };	

enum class Action {
	Fold,
	Call,
	Check,
	Raise
};

struct ActionTaken {
	Action action;
	int amount;
	int raised;
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

