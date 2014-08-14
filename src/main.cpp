#include <iostream>

#include "poker.h"
#include "table.h"
#include "configurator.h"

int main() {

	Table table;

	Configurator config;
	config.Load(&table);
	
	Poker poker;
	poker.startGame(&table);
}
