#ifndef Poker_H
#define Poker_H

#include "enums.h"
#include "table.h"

class Poker {
public:
	void startGame(Table* table);
	GameState gameState;
};

#endif
