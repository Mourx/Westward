#include "Encounter.h"



Encounter::Encounter(int id)
{
	
	ifstream encStream("encounters.json");
	ifstream monStream("enemies.json");

	CharReaderBuilder reader;
	Value obj;
	string errs;
	if (parseFromStream(reader, encStream, &obj, &errs)) {
		cout << errs << endl;
	};
	for (Value v : obj) {
		if (v["id"] == id) {
			area.assign(v["area"].asString);
			Value arr = v["enemies"];
			for (Value en : arr) {
				possibleEnemies.push_back(en.asInt);
			}
			minChallenge = v["minChallenge"].asFloat;
			maxChallenge = v["maxChallenge"].asFloat;
			encounterLevel = v["level"].asInt;
			break;
		}
	}




}


Encounter::~Encounter()
{
}

vector<Combatant*> Encounter::getEnemies() {
	vector<Combatant*> e;
	return e;
}