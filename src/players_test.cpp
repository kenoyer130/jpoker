#include "players.h"
#include "gtest/gtest.h"

class PlayersTest : public ::testing::Test {

};

TEST(PlayersTest, EarlyPositionTest) {

	// assemble
	Configurator config;
	Players players(config.Get());

	// set dealer to last player
	players.Dealer = players.items.size() - 1;

	Player& testPlayer = *players.items[1];
	
	// act
	int position = players.getPosition(testPlayer);

	// assert
	EXPECT_EQ(1, position);
}

TEST(PlayersTest, MiddlePositionTest) {

	// assemble
	Configurator config;
	Players players(config.Get());

	// set dealer to last player
	players.Dealer = 0;

	Player& testPlayer = *players.items[4];
	
	// act
	int position = players.getPosition(testPlayer);

	// assert
	EXPECT_EQ(4, position);
}

TEST(PlayersTest, LatePositionTest) {

	// assemble
	Configurator config;
	Players players(config.Get());

	// set dealer to last player
	players.Dealer = 0;

	Player& testPlayer = *players.items[8];
	
	// act
	int position = players.getPosition(testPlayer);

	// assert
	EXPECT_EQ(1, position);
}

TEST(PlayersTest, DealerTest) {

	// assemble
	Configurator config;
	Players players(config.Get());

	// set dealer to last player
	players.Dealer = 0;

	Player& testPlayer = *players.items[0];
	
	// act
	int position = players.getPosition(testPlayer);

	// assert
	EXPECT_EQ(-1, position);
}
