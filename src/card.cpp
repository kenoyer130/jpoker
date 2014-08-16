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
	
	if(number> 0 && number<10) {
		value += std::to_string(number + 1);
	} else {
		switch(number){
		case 10:
			value += "Jack";
			break;
		case 11:
			value += "Queen";
			break;
       case 12:
			value += "King";
			break;
		case 0:
			value += "Ace";
			break;
		}
	}

	value += " of ";

	int val = static_cast<int>(suite);
	value += SuiteStrings[val];

	return value;
}

