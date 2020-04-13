#include "Combatant.h"



Combatant::Combatant(Enemy* e, bool bPlayer)
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
