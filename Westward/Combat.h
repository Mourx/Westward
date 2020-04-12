#pragma once
#include <vector>
#include "Combatant.h"
#include "Tile.h"
#include "Encounter.h"

class Combat
{
public:
	Combat(std::vector<Combatant> playerMain, std::vector<Combatant> playerSupport, Encounter encounter);
	~Combat();
	std::vector<Combatant> units;
	std::vector<std::vector<Tile>> combatGrid;
};


