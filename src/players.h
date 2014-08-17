// circular queue representing the players around the table.
// where the dealer is the current pointer.
// this also allows us to ask questions specific to poker such as player position in regards to the dealer.

#ifndef Players_H
#define Players_H

#include <vector>
#include <memory>
#include <random>

#include "configurator.h"
#include"player.h"

class Players {

public:

Player& Dealer();
Player& BigBlind();
Player& SmallBlind();
 
// constructor
Players(Configuration config);

Player& next(const Player& player);

// moves the dealer button to the next player on the left
// also resets the big and little blinds.
void nextDealer();

void clearDealer();

void clearBlinds();

int ante(int bigBlind, int smallBlind);

int getPosition(const Player& player);

// removes player
void remove(Player& player);

std::vector<std::unique_ptr<Player>> items;


};

#endif