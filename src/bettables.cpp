#include "bettables.h"

BetTables::BetTables(){
	seedHoleCards();
}

void BetTables::seedHoleCards() {

	// raw percent chance to bet not including position.
	
	// AA,KK,QQ,JJ
	this->HoleCards[HoleCard(0,0).key(), 150];
	this->HoleCards[HoleCard(12,12).key(), 150];
	this->HoleCards[HoleCard(11,11).key(), 150];
	this->HoleCards[HoleCard(10,10).key(), 150];

	// 10,AK
	this->HoleCards[HoleCard(9,9).key(), 110];
	this->HoleCards[HoleCard(0,12).key(), 110];

	// 99, AQ
	this->HoleCards[HoleCard(8,8).key(), 80];
	this->HoleCards[HoleCard(0,11).key(), 80];

    // 88, AJ, KQ
	this->HoleCards[HoleCard(7,7).key(), 70];
	this->HoleCards[HoleCard(0,10).key(), 70];
	this->HoleCards[HoleCard(12,11).key(), 70];

	// 77, KJ, QJ, JT
	this->HoleCards[HoleCard(6,6).key(), 60];
	this->HoleCards[HoleCard(12,10).key(), 60];
	this->HoleCards[HoleCard(11,10).key(), 60];
	this->HoleCards[HoleCard(10,9).key(), 60];
}

