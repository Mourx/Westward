#pragma once
#include "EnemyDefinitions.h"

class Combatant
{
public:
	Combatant(Enemy* e);
	~Combatant();
	Enemy* unit;
};

