#include "./stockai.h"
#include "jout.h"

#include <cmath>

ActionTaken StockAI::getAction(HandState handState) {
  	
	handState.cards.push_back(handState.holeCard[0]);
	handState.cards.push_back(handState.holeCard[1]);

	HandRank hand = Hand(handState.cards).getRanking();

	for (int i = 0; i < handState.cards.size(); i++) {
		debug << " " << handState.cards[i].ToString();
	}

	debug << "position: " << PositionStrings[static_cast<int>(handState.position)] <<"\n";

	ActionTaken result;

    // get the current rank for our hand
    int rank{0};

	if(handState.gameState == GameState::PreFlop) {
		rank = getPreFlopDecision(hand, handState);

		debug << "preflop rank: " << rank << "\n";
	}

	// modify rank based off position

    // if worst position subtract 2
    if (handState.position == Position::Early) {
		debug << "early position -2\n";	
		rank -= 2;
   }

	// if mid position subtract 1
    if (handState.position == Position::Middle) {
		debug << "mid position -1\n";	
		rank -= 2;
   }
	
   // if late
   if(handState.position == Position::Late) {
	   debug << "late position +1\n";	
	   rank += 1;
   }

   // if dealer add 1
   if(handState.position == Position::Dealer) {
	   debug << "dealer position +1\n";
	   rank += 1;
   }

   // if pressured from raises
   rank -= handState.raise;

   if(handState.raise > 0) {
	   debug << "rank after raises " << handState.raise  << ": " << rank;
   }
   
   debug << "final rank: " << rank << "\n";

   // if no bet and non-raise hand just check
   if(handState.currentbet == 0 && rank < 3) {
	   result.action = Action::Check;
   } else if (rank > 0 && rank <3) {
	   // if bet and decent hand just call
	   result.action = Action::Call;
   } else if (rank > 2) {
	   // good hand so raise
	   result.action = Action::Raise;
	   result.amount = 200;
   } else {
	   // bail!
	   result.action = Action::Fold;
   }

	return result;
}

int StockAI::getPreFlopDecision(HandRank hand, HandState handState) {

    // bet on high pairs
	if(hand.rank == Rank::OnePair && hand.card.number > 9) {
		return 5;
	}
	
// bet on on pairs
	if(hand.rank == Rank::OnePair) {
		return 4;
	}

// any high straights or flushes
if(hand.rank > Rank::OnePair && hand.card.number > 9) {
return 3;
}
		
	// bet any high card
	if(handState.holeCard[0].number > 9 || handState.holeCard[1].number > 9) {
		return 2;
	}

	// bet any small spreads
	if(abs(handState.holeCard[0].number - handState.holeCard[1].number) == 1) {
		return 1;
	}
	
	return 0;
 }


