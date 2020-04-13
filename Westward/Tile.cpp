#include "Tile.h"



Tile::Tile()
{
}


Tile::~Tile()
{
}


void Tile::setCombatant(Combatant* c) {
	unit = c;
	bHasCombatant = true;
}

Combatant* Tile::getCombatant() {
	return unit;
}

bool Tile::hasCombatant() {
	return bHasCombatant;
}