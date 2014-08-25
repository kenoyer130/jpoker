#include "configurator.h"


//todo: read from config file
Configuration Configurator::Get() { 

	Configuration config;

	config.SmallBlind = 100;
	config.BigBlind = 200;
	config.StartingChips = 2000;

	// how often do we raise blinds?
	config.HandBlinds = 5;
	
	config.PlayerNames = {{"Jim", "Bob","Joe","Slack","Bot","Rick","Amy","Sara"}};
	return config;
}
