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

	if (!font.loadFromFile("arial.ttf"));

	for (int j = 0; j < combatGrid.size();j++) {
		TileRow* tr = combatGrid[j];
		for (int i = 0; i < tr->getRow().size(); i++) {
			Tile* tile = tr->getTile(i);
			sf::Text text;
			
			text.setFont(font);
			if (tile->getCombatant() != NULL) {
				text.setString(tile->getCombatant()->unit->getName());
				tile->getCombatant()->unit->setPosition(100+ i * 50, 100 + j * 50);
			}
			else {
				text.setString("| | | |");
			}
			
			
			text.setPosition(i*50,j*50);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(14);
			combatGridText.push_back(text);
		}
	}
	
	cursorTexture.loadFromFile("cursor.png");
	cursor.setTexture(cursorTexture);
	ShowGrid();
	
	generateTurnOrder();
}

void Combat::setCursorPosition(int x, int y) {
	cursor.setPosition(x, y);
}

void Combat::Draw(sf::RenderWindow* window) {
	window->draw(cursor);
	for (sf::Text t : combatGridText) {
		window->draw(t);
	}
	for (Combatant* c : units) {
		window->draw(c->unit->getSprite());
	}
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

Combatant* Combat::getUnit(int index) {
	return(units[index]);
}

int Combat::getUnitsSize() {
	return units.size();
}

bool Combat::DoAction(int action) {
	cout << endl;
	cout << turnOrder[turn]->unit->getName() << "'s turn. Choose Action:  \n0\tAttack\n1\tDefend" << endl;
	if (turnOrder[turn]->IsPlayer()) {
		if (phase == ACTION) {
			CombatActions acts = CombatActions(action);
			switch (acts) {
			case ATTACK:
				ShowGrid();
				cout << "Choose target:  \n4\t5\t6\t7\n0\t1\t2\t3" << endl;
				phase = TARGET;
				return true;
				//getline(cin, actionStr);
				//action = stoi(actionStr);
				break;
			case DEFEND:
				//add defense modifier
				bValidAction = true;
				AdvanceTurn();
				return true;
				break;
			default:
				return false;
			}
		}

		if (phase == TARGET){

			if (combatGrid[action%4]->TileContains(action/4)) {
				//attack target
				Attack(combatGrid[action % 4]->getTile(action/4)->getCombatant());
				bValidTarget = true;
			}
			else {
				cout << "Please select a valid target" << endl;
			}
		}
	}
	else {
		std::vector<Combatant*> playerUnits = getUnitList(true);
		Attack(playerUnits[rand() % playerUnits.size()]);
	}
}

void Combat::Attack(Combatant*) {
	cout << "Kapow!" << endl;
}

CombatPhases Combat::getPhase() {
	return phase;
}

std::vector<Combatant*> Combat::getUnitList(bool bPlayer) {
	std::vector<Combatant*> list;
	for (Combatant* c : units) {
		if (bPlayer){
			if (c->IsPlayer()) {
				list.push_back(c);
			}
		}
		else {
			if (!c->IsPlayer()) {
				list.push_back(c);
			}
		}
	}
	return list;
}

void Combat::AdvanceTurn() {
	turnOrder[turn]->unit->tickModifiers();
	turn++;
	if (turn >= turnOrder.size()) {
		turn = 0;

	}
	if (!turnOrder[turn]->IsPlayer()) {
		DoAction(0);
		DoAction(0);
	}
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
				
			}
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