#ifndef Poker_H
#define Poker_H

#include "enums.h"
#include "table.h"

class Poker {
public:
	Poker();
	void StartGame();

private:
	std::unique_ptr<Table> table;
	std::unique_ptr<Players> players;

	GameState gameState;

	int bigBlind;
	int smallBlind;

	void clearPlayers();
	void printState();
	void startHand();
	void dealHoleCards();
};

#endif
