#pragma once
#include "Combat.h"
#include <iostream>
#include "json.h"
#include <fstream>
using namespace std;

int main() {
	cout << "A group of Enemies Approach!" << endl << endl;
	vector<Combatant*> playerMain;
	vector<Combatant*> playerSupport;
	playerMain.push_back(new Combatant(new Enemy(1),true));
	playerSupport.push_back(new Combatant(new Enemy(2),true));
	Encounter* encounter = new Encounter(1);
	Combat* combat = new Combat(playerMain,playerSupport,encounter);
	combat->RunCombat();
	for (Combatant* c : encounter->getEnemies()) {
		//cout << "name: " << c->unit->getName() << endl;
	}
	

	getchar();
	return 0;
}