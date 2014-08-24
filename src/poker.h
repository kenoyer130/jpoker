#ifndef Poker_H
#define Poker_H

#include "enums.h"
#include "table.h"

using namespace std;

class Poker {
public:
	Poker();
	void StartGame();

private:
	std::unique_ptr<Table> table;
	std::unique_ptr<Players> players;

    std::vector<Card> cards;

	int currentbet {0};
	
	GameState gameState;

	int bigBlind {0};
	int smallBlind {0};
	int handBlinds {0};
	int handCount {0};

	void resetPlayers();
	void takeActions();
	void printState();
	void startHand();
	void dealHoleCards();
	void dealCards(int number);
	void handOver();
	void playerWon(int playerIndex);
	void clearScreen();
	
};

#endif
