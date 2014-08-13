#include <string>

#include "card.h"

std::string Card::ToString() {

	std::string value;
	
	if(number>10) {
		value += std::to_string(number);
	} else {
		switch(number){
		case 11:
			value += "J";
			break;
		case 12:
			value += "Q";
			break;
       case 13:
			value += "K";
			break;
		case 14:
			value += "A";
		}
	}

	value += " of ";

	int val = static_cast<int>(suite);
	value += SuiteStrings[val];

	return value;
}

