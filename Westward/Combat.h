#pragma once
#include <vector>
#include "Combatant.h"
#include "TileRow.h"
#include "Encounter.h"

class Combat
{
public:
	Combat(std::vector<Combatant*> playerMain, std::vector<Combatant*> playerSupport, Encounter* encounter);
	~Combat();
	std::vector<Combatant*> units;
	std::vector<Combatant*> enemyBack;
	std::vector<Combatant*> enemyFront;
	std::vector<Combatant*> playerFront;
	std::vector<Combatant*> playerBack;
	std::vector<TileRow*> combatGrid;
};


