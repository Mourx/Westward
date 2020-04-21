#include "Combatant.h"



Combatant::Combatant(CombatActor* e, bool bPlayer)
{
	unit = e;
	bIsPlayer = bPlayer;
}


Combatant::~Combatant()
{
}

bool Combatant::IsPlayer() {
	return bIsPlayer;
}
