#pragma once
#include "Combatant.h"

class Tile
{
public:
	Tile();
	~Tile();
	void setCombatant(Combatant* c);
	bool hasCombatant();
	Combatant* getCombatant();
private:
	Combatant* unit;
	bool bHasCombatant;

};

