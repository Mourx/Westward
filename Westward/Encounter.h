#pragma once
#include "Combatant.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "json.h"
using namespace std;
using namespace Json;
class Encounter
{
public:
	Encounter(int lvl);
	~Encounter();
	vector<Combatant*> getEnemies();
private:
	vector<Combatant*> enemies;
	vector<int> possibleEnemies;
	string area = "";
	float minChallenge;
	float maxChallenge;
	int encounterLevel = 0;
};

