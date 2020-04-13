#include "Combat.h"
#include <random>
#include <ctime>


Combat::Combat(std::vector<Combatant*> playerMain, std::vector<Combatant*> playerSupport, Encounter* encounter)
{
	std::srand(std::time(nullptr));
	for (Combatant* c : playerMain) {
		units.push_back(c);
		if (c->unit->getFrontLine()) {
			playerFront.push_back(c);
		}
		else {
			playerBack.push_back(c);
		}
	}
	for (Combatant* c : playerSupport) {
		units.push_back(c);
		if (c->unit->getFrontLine()) {
			playerFront.push_back(c);
		}
		else {
			playerBack.push_back(c);
		}
	}
	std::vector<Combatant*> enemies = encounter->getEnemies();
	for (Combatant* c : enemies) {
		units.push_back(c);
		if (c->unit->getFrontLine()) {
			enemyFront.push_back(c);
		}
		else {
			enemyBack.push_back(c);
		}
	}

	TileRow* pRFront = new TileRow();
	int r = (rand() % 4);
	for (Combatant* c : playerFront) {
		while (pRFront->TileContains(r)) {
			r = (rand() % 4);
		}
		pRFront->getTile(r)->setCombatant(c);
	}
	TileRow* pRBack = new TileRow();
	for (Combatant* c : playerBack) {
		while (pRBack->TileContains(r)) {
			r = (rand() % 4);
		}
		pRBack->getTile(r)->setCombatant(c);
	}
	TileRow* eRFront = new TileRow();
	for (Combatant* c : enemyFront) {
		while (eRFront->TileContains(r)) {
			r = (rand() % 4);
		}
		eRFront->getTile(r)->setCombatant(c);
	}
	TileRow* eRBack = new TileRow();
	for (Combatant* c : enemyBack) {
		while (eRBack->TileContains(r)) {
			r = (rand() % 4);
		}
		eRBack->getTile(r)->setCombatant(c);
	}
	combatGrid.push_back(eRBack);
	combatGrid.push_back(eRFront);
	combatGrid.push_back(pRFront);
	combatGrid.push_back(pRBack);
	int row = 0;
	for (TileRow* tr : combatGrid) {
		for (int i = 0; i < tr->getRow().size();i++) {
			Tile* tile = tr->getTile(i);
			if (tile->hasCombatant()) {
				cout << tile->getCombatant()->unit->getName() << "\t";
			}
			else {
				cout << "_ _ _ _\t";
			}
		}
		cout << endl;
		if (++row == 2) {
			cout << endl;
		}
	}

}


Combat::~Combat()
{
}
