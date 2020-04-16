#pragma once
#include "EnemyDefinitions.h"
#include <SFML/Graphics.hpp>
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

