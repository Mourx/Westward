#include "Combat.h"



Combat::Combat(std::vector<Combatant*> playerMain, std::vector<Combatant*> playerSupport, Encounter* encounter)
{
	for (Combatant* c : playerMain) {
		units.push_back(c);
	}
	for (Combatant* c : playerSupport) {
		units.push_back(c);
	}
	std::vector<Combatant*> enemies = encounter->getEnemies();
	for (Combatant* c : enemies) {
		units.push_back(c);
	}
}


Combat::~Combat()
{
}
