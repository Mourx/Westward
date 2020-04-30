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
	bool IsDead();
	void setDead(bool b) { bIsDead = b; }
private:
	bool bIsPlayer = false;
	bool bIsDead = false;
};

