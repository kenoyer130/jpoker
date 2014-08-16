#ifndef Card_H
#define Card_H

#include <string>
#include <sstream>

#include "enums.h"

class Card {
public:
    int number;
	Suite suite;

	Card();
	Card(int number, Suite suite);
	
	std::string ToString();
};

#endif
