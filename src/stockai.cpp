#include "./stockai.h"
#include "jout.h"

#include <cmath>

ActionTaken StockAI::getAction(HandState handState) {
  	
	handState.cards.push_back(handState.holeCard[0]);
	handState.cards.push_back(handState.holeCard[1]);

	HandRank hand = Hand(handState.cards).getRanking();

	// debug info.
	jout << " " << handState.holeCard[0].ToString() << " " <<  handState.holeCard[1].ToString();
    jout << " " << RankStrings[static_cast<int>(hand.rank)] << "\n";

	// jout << PositionStrings[static_cast<int>(handState.position)] <<"\n";

	ActionTaken result;

    // get the current rank for our hand
    int rank{0};

	if(handState.gameState == GameState::PreFlop) {
		rank = getPreFlopDecision(hand, handState);
	}

    // if worst position subtract 2
    if (handState.position == Position::Early) {
      rank -= 2;
   }

   // if late
   if(handState.position == Position::Late) {
     rank += 1;
   }

   // if dealer add 1
   if(handState.position == Position::Dealer) {
    rank += 1;
   }

   // if pressured from raises
   rank -= handState.raise;
 
   if(rank > 0 && handState.currentbet > 0) {
     result.action = Action::Call;
   } else if (rank > 0) {
	   result.action = Action::Raise;
	   result.amount = 200;
   } else {
	   result.action = Action::Fold;
   }

	// any folds are converted to calls if we get a free bet
	if(handState.currentbet == 0 && result.action == Action::Fold) {
		result.action = Action::Check;
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


