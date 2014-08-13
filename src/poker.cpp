#include <iostream>

#include "enums.h"
#include "poker.h"
#include "table.h"

void Poker::startGame(Table* table) {

	gameState = GameState::GameStart;

	std::cout << "Starting Game! Good luck!\n";
	
	while(gameState!=GameState::GameEnd) {
		switch(gameState){
		case GameState::GameStart:
			table->shuffleDeck();

			gameState= GameState::GameEnd;
			break;
		case GameState::GameEnd:
			break;
		}
	}

    std::cout << "Game Over!\n";
}
