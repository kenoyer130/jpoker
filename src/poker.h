#ifndef Poker_H
#define Poker_H

#include "enums.h"
#include "deck.h"

using namespace std;

class Poker {
public:
	Poker();
	void StartGame();

private:

	Deck deck {};
	
	std::unique_ptr<Players> players;

    std::vector<Card> cards;

	int currentbet {0};
	
	GameState gameState;

	double Pot;
		
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
