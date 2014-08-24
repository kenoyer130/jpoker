#include <string>

#include "card.h"

Card::Card(): number(-1), suite(Suite::HEART) {

}

Card::Card(int number, Suite suite) {
	this->number = number;
	this->suite = suite;
}
	
// stream output operator
ostream& operator << (ostream& os, const Card& c)
{	
	std::string value;
	
	if(c.number<10) {
		value += std::to_string(c.number + 1);
	} else {
		switch(c.number){
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
			break;
		}
	}

	int val = static_cast<int>(c.suite);
	value += SuiteStrings[val];

	os << value;
	
	return os;
}

