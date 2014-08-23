#include "hand.h"

#include <algorithm>
#include <map>
#include <vector>
#include <iostream>

#include "enums.h"

using std::vector;
using std::map;

Hand::Hand(vector<Card> cards) {
    this->cards = cards;
}

HandRank Hand::getRanking() {

    // sort cards
    sort(this->cards.begin(), this->cards.end());
    
    // check from best to worst possible hands.

    HandRank flushHand = getFlush();
    HandRank straightHand = getStraight();
    HandRank sameHand = getSame();
    HandRank pairHand = getPair();
    
    // straight flush
    if(flushHand.rank == Rank::Flush && straightHand.rank == Rank::Straight) {
        HandRank hand;
        hand.card = (flushHand.card.number > straightHand.card.number) ? flushHand.card : straightHand.card;
        hand.rank = Rank::StraightFlush;
                
        return hand;
    }

    // four of a kind
    if(sameHand.rank == Rank::FourKind) {
        return sameHand;
    }

    // full house
    // note a full house techinically has two pair
    if(sameHand.rank == Rank::ThreeKind && pairHand.rank == Rank::TwoPair) {

        sameHand.rank = Rank::FullHouse;
        return sameHand;
    }

    // flush
    if(flushHand.rank==Rank::Flush) {
        return flushHand;
    }

    // straight
    if(straightHand.rank==Rank::Straight) {
        return straightHand;
    }

    // three of a kind
    if(sameHand.rank == Rank::ThreeKind) {
        return sameHand;
    }

    // one or two pair
    if(pairHand.rank == Rank::TwoPair || pairHand.rank == Rank::OnePair) {
        return pairHand;
    }

    // high card
    HandRank handRank;
    handRank.card = this->cards[this->cards.size() -1];
    handRank.rank = Rank::HighCard;

    return handRank;
 }

 HandRank Hand::getFlush() {

     HandRank hand{};
     
     Suite suite = this->cards[0].suite;
     
     // if any card does not match
     for(int i=1; i<this->cards.size(); i++) {
         if(this->cards[i].suite != suite) {
             return hand;
         }
     }

     // if we make it here we got a flush
     hand.rank = Rank::Flush;
     hand.card = this->cards[this->cards.size()-1];

     return hand;
 }

HandRank Hand::getStraight() {
    // since cards are sorted start with first and see if we are in a row

    HandRank hand{};

    Card first = this->cards[0];
    
    for (int i = 1; i < this->cards.size(); i++) {
        if(this->cards[i].number != first.number + i) {
            return hand;
        }
    }   

    // if we made it here we have a straight
    hand.rank = Rank::Straight;
    hand.card = this->cards[this->cards.size()-1];

    return hand;
}

HandRank Hand::getSame() {
    
    int same;
    Card card{};
    
    for (int i = 0; i < this->cards.size(); i++) {
        int count(1);

        for (int j = i + 1; j < this->cards.size(); j++) {
            if(this->cards[i].number!=this->cards[j].number) {
                break;
            }

            count++;
        }

        // set the card and count 
        if(count > same && count > 2) {
            card = this->cards[i];
            same = count;
        }
    }
    
    HandRank hand{};

    // have less then 3 of a kind
    if (same < 3) {
        return hand;
    }

    hand.rank = (same == 4) ? Rank::FourKind : Rank::ThreeKind;
    hand.card = card;

    return hand;
}

HandRank Hand::getPair() {
    // place pairs in map to not have dupe pairs
    // in the case of 3-4 of a kind etc
    map<int, Card> m;

    for (int i = 0; i < this->cards.size(); i++) {
        int count(0);

        for (int j  = i; j < this->cards.size(); j++) {
            if (this->cards[j].number == this->cards[i].number) {
                count++;
            }
        }

        if (count == 2 && m.find(this->cards[i].number) == m.end()) {
            m[this->cards[i].number] = this->cards[i];
        }
    }

    // now put pairs into vector and sort
    vector<Card> pairs;

    for (auto& card : m) {
        pairs.push_back(card.second);
    }

    sort(pairs.begin(), pairs.end());

    HandRank hand{};

    if (pairs.size() == 0) {
        return hand;
    }

    hand.card = pairs[pairs.size()-1];

    hand.rank = (pairs.size() == 1) ? Rank::OnePair : Rank:: TwoPair;

    return hand;
}
