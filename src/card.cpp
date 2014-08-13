#include <string>

#include "card.h"

std::string Card::ToString() {

	std::string value;
	
	if(number<10) {
		value += std::to_string(number + 1);
	} else {
		switch(number){
		case 10:
			value += "J";
			break;
		case 11:
			value += "Q";
			break;
       case 12:
			value += "K";
			break;
		case 13:
			value += "A";
		}
	}

	value += " of ";

	int val = static_cast<int>(suite);
	value += SuiteStrings[val];

	return value;
}

