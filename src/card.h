#ifndef Card_H
#define Card_H

#include <string>
#include <sstream>
#include <iostream>

#include "enums.h"
#include "jout.h"

using std::ostream;

class Card {
	
public:
	
    int number;
	Suite suite;

	// constructors
	Card();
	Card(int number, Suite suite);

	// sorter
	bool operator<(const Card &rhs) const { return number < rhs.number; }

    friend ostream& operator<<(ostream& os, const Card& c);
};

#endif
