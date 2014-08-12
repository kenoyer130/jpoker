#include <iostream>

#include "enums.h"
#include "poker.h"
#include "table.h"

void Poker::startGame(Table* table) {

	gameState = GameState::GameStart;

	while(gameState!=GameState::GameStart) {
		switch(gameState){
		case GameState::GameStart:
			table->shuffleDeck();

			gameState= GameState::GameStart;
			break;
		}
	}
}
