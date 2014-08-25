#ifndef Configurator_H
#define  Configurator_H

#include <vector>
#include <string>

struct Configuration {

	double SmallBlind {0.0};
	double BigBlind {0.0};
	int StartingChips {0};

	int HandBlinds {0};

	bool AutoMode {false};
	
	std::vector<std::string> PlayerNames;
};


class Configurator {
public:
	Configuration Get();
};

#endif
