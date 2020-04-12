#pragma once
#include "Combatant.h"
#include <vector>
using namespace std;
class Encounter
{
public:
	Encounter();
	~Encounter();
	vector<Combatant> getEnemies();
private:
	vector<Combatant> enemies;
};

