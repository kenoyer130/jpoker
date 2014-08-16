#include <iostream>

#include "enums.h"
#include "poker.h"
#include "table.h"

void Poker::startGame(Table* table) {

	gameState = GameState::HandStart;

	std::cout << "Starting Game! Good luck!\n";
	
	while(gameState!=GameState::GameEnd) {
		switch(gameState){

		case GameState::HandStart:

			table->ShuffleDeck();
			table->DealHoleCards();

			std::cout << "Your hole cards: " << table->You().HoleCard[0].ToString() << " " << table->You().HoleCard[1].ToString() << "\n\n";
			
			gameState= GameState::GameEnd;
			break;

		case GameState::GameEnd:
			break;
		}
	}

    std::cout << "Game Over!\n";
}
