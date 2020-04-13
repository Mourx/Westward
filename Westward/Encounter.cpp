#include "Encounter.h"
#include <random>
#include <ctime>


Encounter::Encounter(int id)
{
	std::srand(std::time(nullptr));
	ifstream encStream("encounters.json");
	CharReaderBuilder reader;
	Value obj;
	string errs;
	if (parseFromStream(reader, encStream, &obj, &errs)) {
		//cout << errs << endl;
	};
	for (Value v : obj) {
		if (v["id"] == id) {
			area.assign(v["area"].asString());
			Value arr = v["enemies"];
			for (Value en : arr) {
				possibleEnemies.push_back(en.asInt());
			}
			minChallenge = v["minChallenge"].asFloat();
			maxChallenge = v["maxChallenge"].asFloat();
			encounterLevel = v["level"].asInt();
			break;
		}
	}

	float currentChallenge = 0;
	while (currentChallenge < maxChallenge && enemies.size() < 4) {
		if (currentChallenge >= minChallenge && rand() % 30 > 25) {
			break;
		}
		int r = (rand() % possibleEnemies.size()) + 1;
		enemies.push_back(new Combatant(new Enemy(r)));
		currentChallenge = 0;
		for (Combatant* c : enemies) {
			currentChallenge += c->unit->getChallengeValue();
		}
	}
}


Encounter::~Encounter()
{
}

vector<Combatant*> Encounter::getEnemies() {
	return enemies;
}