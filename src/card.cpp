#include <string>

#include "card.h"

Card::Card() {
	
}

Card::Card(int number, Suite suite) {
	this->number = number;
	this->suite = suite;
}

std::string Card::ToString() {

	std::string value;
	
	if(number<9) {
		value += std::to_string(number + 1);
	} else {
		switch(number){
		case 9:
			value += "Jack";
			break;
		case 10:
			value += "Queen";
			break;
       case 11:
			value += "King";
			break;
		case 12:
			value += "Ace";
			break;
		}
	}

	value += " of ";

	int val = static_cast<int>(suite);
	value += SuiteStrings[val];

	return value;
}

