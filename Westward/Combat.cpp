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

	playerSquare.loadFromFile("tiles.png", sf::IntRect(0, 0, 32, 32));
	enemySquare.loadFromFile("tiles.png", sf::IntRect(32, 0, 32, 32));

	if (!font.loadFromFile("arial.ttf"));

	for (int j = 0; j < combatGrid.size();j++) {
		TileRow* tr = combatGrid[j];
		for (int i = 0; i < tr->getRow().size(); i++) {
			Tile* tile = tr->getTile(i);
			sf::Text text;
			
			text.setFont(font);
			if (tile->getCombatant() != NULL) {
				text.setString(tile->getCombatant()->unit->getName());
				tile->getCombatant()->unit->setPosition(60+ i * 50, 60 + j * 50);
			}
			else {
				text.setString("| | | |");
			}
			
			
			text.setPosition(i*50,j*50);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(14);
			combatGridText.push_back(text);
			sf::Sprite* spr = new sf::Sprite();
			spr->setPosition(60 + i * 50, 60 + j * 50);
			if (j >= 2) {
				spr->setTexture(enemySquare);
			}
			else {
				spr->setTexture(playerSquare);
			}
			combatGridIcons.push_back(spr);
		}
	}
	
	backgroundTexture.loadFromFile("grass.png");
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);

	dialogTexture.loadFromFile("dialogOptions.png");
	dialog.setTexture(dialogTexture);
	dialog.setPosition(50, 250);

	statsTexture.loadFromFile("dialogStats.png");
	stats.setTexture(statsTexture);
	stats.setPosition(250, 50);

	combatTexture.loadFromFile("dialogCombat.png");
	combat.setTexture(combatTexture);
	combat.setPosition(50, 50);

	heartTexture.loadFromFile("heart.png");
	heart.setTexture(heartTexture);
	heart.setPosition(260, 60);
	inspectHealth.setFont(font);
	inspectHealth.setCharacterSize(12);
	inspectHealth.setPosition(280, 60);

	inspectDefense.setFont(font);
	inspectDefense.setCharacterSize(12);
	inspectDefense.setPosition(280, 85);

	inspectDamage.setFont(font);
	inspectDamage.setCharacterSize(12);
	inspectDamage.setPosition(280, 110);

	inspectName.setFont(font);
	inspectName.setCharacterSize(12);
	inspectName.setPosition(280, 135);

	cursorTexture.loadFromFile("cursor.png");
	cursorTarget.setTexture(cursorTexture);
	cursorAction.setTexture(cursorTexture);
	cursorAction.setScale(2, 0.8);
	ShowGrid();
	
	generateTurnOrder();
	generateActions();
}

void Combat::setCursorPosition(Combatant* targ) {
	target = targ;
	cursorTarget.setPosition(target->unit->getPosition().x, target->unit->getPosition().y);
	updateStrings(target);
	
}

void Combat::updateStrings(Combatant* targ) {
	inspectHealth.setString(to_string((int)targ->unit->getCurrentHealth()));
	inspectName.setString(targ->unit->getName());
	inspectDamage.setString(to_string((int)targ->unit->getCurrentHealth()));
	inspectDefense.setString(to_string((int)targ->unit->getCurrentDefense()));
}

void Combat::setCursorPosition(ActionPrompt* act) {
	cursorAction.setPosition(act->name.getPosition().x-5,act->name.getPosition().y-5);
}

int Combat::getActionAmount() {
	return availableActions.size();
}

void Combat::Draw(sf::RenderWindow* window) {
	window->draw(background);
	window->draw(combat);
	window->draw(dialog);
	window->draw(stats);
	window->draw(heart);
	window->draw(inspectHealth);
	window->draw(inspectDefense);
	window->draw(inspectDamage);
	window->draw(inspectName);
	
	window->draw(cursorAction);
	for (ActionPrompt* a : availableActions) {
		window->draw(a->name);
	}
	for (sf::Sprite* s : combatGridIcons) {
		window->draw(*s);
	}
	window->draw(cursorTarget);
	//for (sf::Text t : combatGridText) {
	//	window->draw(t);
	//}
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

void Combat::generateActions() {
	availableActions.clear();
	if (turnOrder[turn]->IsPlayer() && phase == ACTION) {
		availableActions.push_back(new ActionPrompt(ATTACK));
		availableActions.push_back(new ActionPrompt(DEFEND));
	}
	for (int i = 0; i < availableActions.size();i++) {
		availableActions[i]->name.setPosition(75 + i * 100, 280);
	}
}

void Combat::changePhase(CombatPhases p) {
	phase = p;
	generateActions();
}

ActionPrompt* Combat::getAction(int actionIndex) {
	return availableActions[actionIndex];
}

bool Combat::DoAction(CombatActions action) {
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
				break;
			default:
				return false;
			}
		}
	}
	while(!turnOrder[turn]->IsPlayer()){
		std::vector<Combatant*> playerUnits = getUnitList(true);
		Attack(turnOrder[turn],playerUnits[rand() % playerUnits.size()]);
		AdvanceTurn();
	}
	return true;
}

bool Combat::DoAction(int target) {
	if (units[target] != turnOrder[turn]) {
		//attack target
		Attack(turnOrder[turn], units[target]);
		bValidTarget = true;
		phase = ACTION;
		AdvanceTurn();
	}
	else {
		cout << "Please select a valid target" << endl;
	}
	while (!turnOrder[turn]->IsPlayer()) {
		std::vector<Combatant*> playerUnits = getUnitList(true);
		Attack(turnOrder[turn],playerUnits[rand() % playerUnits.size()]);
		AdvanceTurn();
	}
	return true;
}

void Combat::Attack(Combatant* user, Combatant* target) {
	float attack = user->unit->getCurrentDamage();
	float defense = target->unit->getCurrentDefense();
	float levelU = user->unit->getLevel();
	float levelT = target->unit->getLevel();
	float damage = (attack * levelU) - (defense * levelT);
	if (damage <= 0) damage = 0;
	target->unit->modifyHealth(damage);
	if (target->unit->checkDead()) {
		target->setDead(target->unit->checkDead());
		for (int i = 0; i < turnOrder.size(); i++) {
			if (turnOrder[i] == target) {
				cout << target->unit->getName() << endl;
				turnOrder.erase(turnOrder.begin() + i);
				
				if (turn == i) {
					turn--;
				}
				i--;
				break;
				
			}
			
		}
	}
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
	for (int i = 0; i < units.size();i++) {
		units[i]->unit->calcStats();
		if (units[i]->IsDead()) {
			units.erase(units.begin()+i);
			i--;
		}
	}
	updateStrings(target);
	if (turn >= turnOrder.size()) {
		generateTurnOrder();
		turn = 0;

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
		c->unit->ApplyModifiers();
		c->unit->calcStats();
	}
}