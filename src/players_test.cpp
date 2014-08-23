#include "players.h"
#include "gtest/gtest.h"

class PlayersTest : public ::testing::Test {

};

TEST(PlayersTest, EarlyPositionTest) {

	// assemble
	Configurator config;
	Players players(config.Get());

	// set dealer to last player
	players.Dealer = 0;

	Player& testPlayer = *players.items[1];
	
	// act
	Position position = players.getPosition(testPlayer);

	// assert
	EXPECT_EQ(Position::Early, position);
}

TEST(PlayersTest, MiddlePositionTest) {

	// assemble
	Configurator config;
	Players players(config.Get());

	// set dealer to last player
	players.Dealer = 0;

	Player& testPlayer = *players.items[4];
	
	// act
	Position position = players.getPosition(testPlayer);

	// assert
	EXPECT_EQ(Position::Middle, position);
}

TEST(PlayersTest, LatePositionTest) {

	// assemble
	Configurator config;
	Players players(config.Get());

	// set dealer to last player
	players.Dealer = 0;

	Player& testPlayer = *players.items[8];
	
	// act
	Position position = players.getPosition(testPlayer);

	// assert
	EXPECT_EQ(Position::Late, position);
}

TEST(PlayersTest, DealerTest) {

	// assemble
	Configurator config;
	Players players(config.Get());

	// set dealer to last player
	players.Dealer = 0;

	Player& testPlayer = *players.items[0];
	
	// act
	Position position = players.getPosition(testPlayer);

	// assert
	EXPECT_EQ(Position::Dealer, position);
}
