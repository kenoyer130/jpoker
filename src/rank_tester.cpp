#include "rank_tester.h"

#include <random>

// poor mans unit tests
int main() {
	RankTester tester;
	tester.Run();
}

void RankTester::Run() {

	vector<Card> royalFlush;
	royalFlush.push_back(Card(13, Suite::SPADE));
	royalFlush.push_back(Card(12, Suite::SPADE));
	royalFlush.push_back(Card(11, Suite::SPADE));
	royalFlush.push_back(Card(10, Suite::SPADE));
	royalFlush.push_back(Card(9, Suite::SPADE));
	
	Assert("Royal Flush", royalFlush, Rank::StraightFlush, 13);

	vector<Card> fourKind;
	fourKind.push_back(Card(5, Suite::SPADE));
	fourKind.push_back(Card(5, Suite::HEART));
	fourKind.push_back(Card(5, Suite::DIAMOND));
	fourKind.push_back(Card(5, Suite::CLUBS));
	fourKind.push_back(Card(9, Suite::SPADE));
	
	Assert("four kind", fourKind, Rank::FourKind, 5);

	vector<Card> flush;
	flush.push_back(Card(2, Suite::CLUBS));
	flush.push_back(Card(3, Suite::CLUBS));
	flush.push_back(Card(7, Suite::CLUBS));
	flush.push_back(Card(9, Suite::CLUBS));
	flush.push_back(Card(5, Suite::CLUBS));

	Assert("flush", flush, Rank::Flush, 9);

	vector<Card> straight;
	straight.push_back(Card(2, Suite::CLUBS));
	straight.push_back(Card(4, Suite::HEART));
	straight.push_back(Card(3, Suite::CLUBS));
	straight.push_back(Card(6, Suite::SPADE));
	straight.push_back(Card(5, Suite::CLUBS));

	Assert("Straight", straight, Rank::Straight, 6);

	vector<Card> fullHouse;
	fullHouse.push_back(Card(8, Suite::HEART));
	fullHouse.push_back(Card(4, Suite::SPADE));
	fullHouse.push_back(Card(8, Suite::CLUBS));
	fullHouse.push_back(Card(8, Suite::SPADE));
	fullHouse.push_back(Card(4, Suite::CLUBS));

	Assert("FullHouse", fullHouse, Rank::FullHouse, 8);

	vector<Card> threeKind;
	threeKind.push_back(Card(13, Suite::HEART));
	threeKind.push_back(Card(13, Suite::SPADE));
	threeKind.push_back(Card(13, Suite::CLUBS));
	threeKind.push_back(Card(7, Suite::SPADE));
	threeKind.push_back(Card(4, Suite::CLUBS));

	Assert("ThreeKind", threeKind, Rank::ThreeKind, 13);

	vector<Card> twoPair;
	twoPair.push_back(Card(11, Suite::HEART));
	twoPair.push_back(Card(10, Suite::SPADE));
	twoPair.push_back(Card(4, Suite::CLUBS));
	twoPair.push_back(Card(11, Suite::SPADE));
	twoPair.push_back(Card(10, Suite::CLUBS));

	Assert("TwoPair", twoPair, Rank::TwoPair, 11);

	vector<Card> onePair;
	onePair.push_back(Card(10, Suite::HEART));
	onePair.push_back(Card(11, Suite::SPADE));
	onePair.push_back(Card(10, Suite::CLUBS));
	onePair.push_back(Card(2, Suite::SPADE));
	onePair.push_back(Card(4, Suite::CLUBS));

	Assert("OnePair", onePair, Rank::OnePair, 10);

	vector<Card> highCard;
	highCard.push_back(Card(7, Suite::HEART));
	highCard.push_back(Card(11, Suite::SPADE));
	highCard.push_back(Card(10, Suite::CLUBS));
	highCard.push_back(Card(2, Suite::SPADE));
	highCard.push_back(Card(4, Suite::CLUBS));
	
	Assert("HighCard", highCard, Rank::HighCard, 11);
}

void RankTester::Assert(string test, vector<Card> cards, Rank rank, int highCard) {

	this->shuffle(cards);

	Hand hand(cards);
	
	HandRank handRank = hand.getRanking();

	cout << "test: " <<test;
	
	if(rank == handRank.rank && highCard == handRank.card.number) {
		cout << " PASS!\n";
	} else {
		cout << " FAILED";

		cout << " e: " << RankStrings[static_cast<int>(rank)] << " " << highCard;
		cout << " a: " << RankStrings[static_cast<int>(handRank.rank)] << " " << handRank.card.number << "\n";
	}
}

void RankTester::shuffle(vector<Card>& cards) {
    // implements fisher and yates in place shuffle
	std::default_random_engine generator((unsigned int)time(0));

	for(int i = cards.size()-1; i > -1; i --) {
		std::uniform_int_distribution<int> distribution(0,i);
		int j = distribution(generator); 

		Card temp = cards[j];

		cards[j] = cards[i];
		cards[i] = temp;
	}
}
