// circular queue representing the players around the table.
// unlike a regular queue once set we do not add more items. More players can not join the game.
// also items are removed from random locations. Players leave the game as they lose.
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

int Dealer;
int BigBlind;
int SmallBlind;

Player& getDealer();
Player& getBigBlind();
Player& getSmallBlind();
 
// constructor
Players(Configuration config);

int next(const Player& player);
Player& get(int index);
Player& getNext(const Player& player);

int nextPlayerByIndex(int index);

// moves the dealer button to the next player on the left
// also resets the big and little blinds.
void nextDealer();

int ante(int bigBlind, int smallBlind);

int getPosition(const Player& player);

// removes player
void remove(int index);

std::vector<std::unique_ptr<Player>> items;

// returns indexs of all players who haven't folded
vector<int> activePlayers();

private:

void clearDealer();

void clearBlinds();

};

#endif
