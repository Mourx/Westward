#pragma once
#include "EnemyDefinitions.h"
#include <SFML/Graphics.hpp>
class Combatant
{
public:
	Combatant(CombatActor* e, bool bPlayer);
	~Combatant();
	CombatActor* unit;
	bool IsPlayer();
private:
	bool bIsPlayer = false;
};

