#pragma once
#include "EnemyDefinitions.h"

class Combatant
{
public:
	Combatant(Enemy* e, bool bPlayer);
	~Combatant();
	Enemy* unit;
	bool IsPlayer();
private:
	bool bIsPlayer = false;
};

