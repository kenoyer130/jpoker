#include "hand_rank.h"

#include <iostream>

using std::ostream;

ostream& operator << (ostream& os, const HandRank& handRank)
{	
	os  << RankStrings[static_cast<int>(handRank.rank)];
	return os;
}
