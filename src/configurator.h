#ifndef Configurator_H
#define  Configurator_H

#include <vector>
#include <string>

struct Configuration {
	double SmallBlind;
	double BigBlind;
	int StartingChips;
	std::vector<std::string> PlayerNames;
};


class Configurator {
public:
	Configuration Get();
};

#endif
