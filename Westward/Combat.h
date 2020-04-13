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
	bool RunCombat();
	void ShowGrid();
private:
	std::vector<Combatant*> units;
	std::vector<Combatant*> enemyBack;
	std::vector<Combatant*> enemyFront;
	std::vector<Combatant*> playerFront;
	std::vector<Combatant*> playerBack;
	std::vector<Combatant*> turnOrder;
	std::vector<TileRow*> combatGrid;
	void generateTurnOrder();
	bool bIsCombat = false;
	int turn = 0;
};


