#include "hand.h"

Hand::Hand(vector<Card> cards) {
	this->cards = cards;
}

Rank Hand::getRanking() {

	// sort cards
	sort(this->cards.begin(), this->cards.end(),
		 [](const Card& a, const Card & b) -> bool
		 { 
			 return a.number > b.number; 
		 });

	// are we same suite?
	bool flush = sameSuite();
	bool straight = inOrder();
	bool same = sameKind();

	// check from best to worst possible hands.

	// royal flush
	if(this->cards.size() == 5 && flush && straight && this->cards[4].number==13) {
		return Rank::RoyalFlush;
	}
	
	// straight flush
	if(flush && straight) {
		return Rank::StraightFlush;
	}

	// four of a kind
	if(this->cards.size() > 3 && same) {
		return Rank::FourKind;
	}

	// full house
	if(this->cards.size() == 5) {
		// first two cards must be the same
		if((this->cards[0].number == this->cards[1].number) &&
		   // third card must match second or fourth
		   (this->cards[1].number == this->cards[2].number || this->cards[2].number == this->cards[3].number) &&
		   // last two cards must be the same
		   (this->cards[3].number == this->cards[4].number)) {
			return Rank::FullHouse;
		}
	}

	// flush
	if(flush) {
		return Rank::Flush;
	}

	// straight
	if(straight) {
		return Rank::Straight;
	}

	// three of a kind
	if(this->cards.size()>2 && same) {
		return Rank::ThreeKind;
	}

    // two pair
	if(this->cards.size()) {

		int pairCount = 0;
		
		for (int i = 0; i < this->cards.size()-1; i++) {
			for(int j = i+1; j < this->cards.size()-1; j++) {
				if(this->cards[i].number ==  this->cards[i].number) {
					pairCount++;
				}
			}
		}

		if(pairCount == 2) {
			return Rank::TwoPair;
		}
	}

    // one pair
	if(same) {
		 return Rank::OnePair;
	 }

	 // high cards
	 if(this->cards[0].number > 9 || this->cards[1].number > 9) {
		 return Rank::HighCard;
	 }

	 // nothing
	 return Rank::Nothing;
 }

 bool Hand::sameKind() {

	 int number = this->cards[0].number;

	 for(int i = 1; i < this->cards.size(); i++) {
		 if(this->cards[i].number!=number) {
			 return false;
		 }
	 }

	 return true;
 }

 bool Hand::sameSuite() {
	 Suite suite = this->cards[0].suite;

	 for(int i=0;i<this->cards.size();i++) {
		 if(this->cards[i].suite!=suite) {
			 return false;
		 }
	 }

	 return true;
 }

 // todo : check for wheels
 bool Hand::inOrder() {
	 int start = this->cards[0].number;

	 for(int i = 1; i < this->cards.size(); i++ ) {
		 if(this->cards[i].number != start + i) {
			return false;
		}
	}

   return true;
}

