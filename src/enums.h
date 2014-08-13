#ifndef Enums_H
#define Enums_H

#include <string>

enum class GameState {
	GameStart,
	GameEnd
};

enum class Suite {
	HEART=0,
		SPADE=1,
		CLOVER=2,
		DIAMOND=3
		};

static const char SuiteStrings[] = { 'H', 'S', 'C', 'D' };	

#endif

