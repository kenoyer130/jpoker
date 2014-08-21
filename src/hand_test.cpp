#include "hand.h"
#include "gtest/gtest.h"

class HandTest : public ::testing::Test {

};

HandRank getHand(vector<Card> cards) {
	Hand hand(cards);
	return hand.getRanking();	
}

TEST(HandTest, RoyalFlush) {

	vector<Card> cards;

	cards.push_back(Card(12, Suite::SPADE));
	cards.push_back(Card(13, Suite::SPADE));
	cards.push_back(Card(9, Suite::SPADE));
	cards.push_back(Card(10, Suite::SPADE));
	cards.push_back(Card(11, Suite::SPADE));

	HandRank handRank = getHand(cards);
	
	EXPECT_EQ(handRank.rank, Rank::StraightFlush);
	EXPECT_EQ(handRank.card.number, 13);
}

TEST(HandTest, FourKind) {
	
	vector<Card> cards;
	cards.push_back(Card(5, Suite::SPADE));
	cards.push_back(Card(5, Suite::HEART));
	cards.push_back(Card(5, Suite::DIAMOND));
	cards.push_back(Card(5, Suite::CLUBS));
	cards.push_back(Card(9, Suite::SPADE));

	HandRank handRank = getHand(cards);
	
	EXPECT_EQ(handRank.rank, Rank::FourKind);
	EXPECT_EQ(handRank.card.number, 5);
}

TEST(HandTest, Flush) {
	vector<Card> cards;
	
	cards.push_back(Card(2, Suite::CLUBS));
	cards.push_back(Card(3, Suite::CLUBS));
	cards.push_back(Card(7, Suite::CLUBS));
	cards.push_back(Card(9, Suite::CLUBS));
	cards.push_back(Card(5, Suite::CLUBS));

	HandRank handRank = getHand(cards);

	EXPECT_EQ(handRank.rank, Rank::Flush);
	EXPECT_EQ(handRank.card.number, 9);
}

TEST(HandTest, Straight) {
	vector<Card> cards;
	
	cards.push_back(Card(2, Suite::CLUBS));
	cards.push_back(Card(4, Suite::HEART));
	cards.push_back(Card(3, Suite::CLUBS));
	cards.push_back(Card(6, Suite::SPADE));
	cards.push_back(Card(5, Suite::CLUBS));

	HandRank handRank = getHand(cards);
	
	EXPECT_EQ(handRank.rank, Rank::Straight);
	EXPECT_EQ(handRank.card.number, 6);
}

TEST(HandTest, FullHouse) {
		
	vector<Card> cards;
	cards.push_back(Card(8, Suite::HEART));
	cards.push_back(Card(4, Suite::SPADE));
	cards.push_back(Card(8, Suite::CLUBS));
	cards.push_back(Card(8, Suite::SPADE));
	cards.push_back(Card(4, Suite::CLUBS));

	HandRank handRank = getHand(cards);
	
	EXPECT_EQ(handRank.rank, Rank::FullHouse);
	EXPECT_EQ(handRank.card.number, 8);
}
	
TEST(HandTest, ThreeKind) {

	vector<Card> cards;
	cards.push_back(Card(13, Suite::HEART));
	cards.push_back(Card(13, Suite::SPADE));
	cards.push_back(Card(13, Suite::CLUBS));
	cards.push_back(Card(7, Suite::SPADE));
	cards.push_back(Card(4, Suite::CLUBS));

	HandRank handRank = getHand(cards);
	
	EXPECT_EQ(handRank.rank, Rank::ThreeKind);
	EXPECT_EQ(handRank.card.number, 13);
}
	
TEST(HandTest, TwoPair) {
	
	vector<Card> cards;
	cards.push_back(Card(11, Suite::HEART));
	cards.push_back(Card(10, Suite::SPADE));
	cards.push_back(Card(4, Suite::CLUBS));
	cards.push_back(Card(11, Suite::SPADE));
	cards.push_back(Card(10, Suite::CLUBS));

	HandRank handRank = getHand(cards);
	
	EXPECT_EQ(handRank.rank, Rank::TwoPair);
	EXPECT_EQ(handRank.card.number, 11);
}

TEST(HandTest, OnePair) {
	
	vector<Card> cards;
	cards.push_back(Card(10, Suite::HEART));
	cards.push_back(Card(11, Suite::SPADE));
	cards.push_back(Card(10, Suite::CLUBS));
	cards.push_back(Card(2, Suite::SPADE));
	cards.push_back(Card(4, Suite::CLUBS));

	HandRank handRank = getHand(cards);
	
	EXPECT_EQ(handRank.rank, Rank::OnePair);
	EXPECT_EQ(handRank.card.number, 10);
}

TEST(HandTest, HighCard) {
	
	vector<Card> cards;
	cards.push_back(Card(7, Suite::HEART));
	cards.push_back(Card(11, Suite::SPADE));
	cards.push_back(Card(10, Suite::CLUBS));
	cards.push_back(Card(2, Suite::SPADE));
	cards.push_back(Card(4, Suite::CLUBS));

	HandRank handRank = getHand(cards);
	
	EXPECT_EQ(handRank.rank, Rank::HighCard);
	EXPECT_EQ(handRank.card.number, 11);
}
