#include "configurator.h"


//todo: read from config file
Configuration Configurator::Get() { 

	Configuration config;
	config.SmallBlind = 100;
	config.BigBlind = 200;
	config.StartingChips = 2000;
	config.PlayerNames = {{"Jim", "Bob","Joe","Slacker","Bot"}};
	return config;
}
