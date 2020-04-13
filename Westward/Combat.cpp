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
	ShowGrid();
	
	generateTurnOrder();
}

Combat::~Combat()
{
}

void Combat::ShowGrid() {
	cout << endl;
	int row = 0;
	for (TileRow* tr : combatGrid) {
		for (int i = 0; i < tr->getRow().size(); i++) {
			Tile* tile = tr->getTile(i);
			if (tile->hasCombatant()) {
				cout << tile->getCombatant()->unit->getName() << "\t";
			}
			else {
				cout << "| | | |\t";
			}
		}
		cout << endl;
		if (++row == 2) {
			cout << endl;
		}
	}
	
	cout << endl;
}


bool Combat::RunCombat() {
	bIsCombat = true;
	while (bIsCombat) {
		for (Combatant* c : turnOrder) {
			c->unit->ApplyModifiers();
		}
		if (turnOrder[turn]->IsPlayer()){
			bool bValidAction = false;
			while (bValidAction == false) {
				string actionStr;
				cout << endl;
				cout << turnOrder[turn]->unit->getName() << "'s turn. Choose Action:  \n0\tAttack\n1\tDefend" << endl;
				getline(cin, actionStr);
				int action = stoi(actionStr);
				bool bValidTarget = false;
				CombatActions acts = CombatActions(action);
				switch (acts) {
				case ATTACK:
					while (bValidTarget == false) {
						ShowGrid();
						cout << "Choose target:  \n4\t5\t6\t7\n0\t1\t2\t3" << endl;
						getline(cin, actionStr);
						action = stoi(actionStr);
						CombatTargets targs = CombatTargets(action);
						switch (targs) {
						case FRONT_ONE:
							if (combatGrid[1]->TileContains(0)) {
								//attack target
								bValidTarget = true;
							}
							else {
								cout << "Please select a valid target" << endl;
							}
							break;
						case FRONT_TWO:
							if (combatGrid[1]->TileContains(1)) {
								bValidTarget = true;
							}
							else {
								cout << "Please select a valid target" << endl;
							}
							break;
						case FRONT_THREE:
							if (combatGrid[1]->TileContains(2)) {
								bValidTarget = true;
							}
							else {
								cout << "Please select a valid target" << endl;
							}
							break;
						case FRONT_FOUR:
							if (combatGrid[1]->TileContains(3)) {
								bValidTarget = true;
							}
							else {
								cout << "Please select a valid target" << endl;
							}
							break;
						case BACK_ONE:
							if (combatGrid[0]->TileContains(0)) {
								bValidTarget = true;
							}
							else {
								cout << "Please select a valid target" << endl;
							}
							break;
						case BACK_TWO:
							if (combatGrid[0]->TileContains(1)) {
								bValidTarget = true;
							}
							else {
								cout << "Please select a valid target" << endl;
							}
							break;
						case BACK_THREE:
							if (combatGrid[0]->TileContains(2)) {
								bValidTarget = true;
							}
							else {
								cout << "Please select a valid target" << endl;
							}
							break;
						case BACK_FOUR:
							if (combatGrid[0]->TileContains(3)) {
								bValidTarget = true;
							}
							else {
								cout << "Please select a valid target" << endl;
							}
							break;
						}
					}
					bValidAction = true;
					break;
				case DEFEND:
					//add defense modifier
					bValidAction = true;
					break;
				}
			}
		}
		turnOrder[turn]->unit->tickModifiers();
		turn++;
		if (turn >= turnOrder.size()) {
			turn = 0;

		}
	}
	return 1;
}

bool CompSpeeds(Combatant* lhs, Combatant* rhs) {
	return lhs->unit->getSpeed() > rhs->unit->getSpeed();
}

void Combat::generateTurnOrder() {
	turnOrder.clear();
	turnOrder = units;

	sort(turnOrder.begin(),turnOrder.end(),CompSpeeds);
	for (Combatant* c : turnOrder) {
		//cout << c->unit->getName() << endl;
	}
}