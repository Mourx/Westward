#pragma once
#include "Combat.h"
#include <iostream>
#include "json.h"
#include <fstream>
using namespace std;

int main() {
	
	vector<Combatant*> playerMain;
	vector<Combatant*> playerSupport;
	playerMain.push_back(new Combatant());
	playerSupport.push_back(new Combatant());
	Encounter* encounter = new Encounter(1);
	Combat* combat = new Combat(playerMain,playerSupport,encounter);


	getchar();
	return 0;
}