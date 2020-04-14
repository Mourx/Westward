#pragma once
#include <vector>
#include "Combatant.h"
#include "TileRow.h"
#include "Encounter.h"
#include "enums.h"
#include <SFML/Graphics.hpp>
class Combat
{
public:
	Combat(std::vector<Combatant*> playerMain, std::vector<Combatant*> playerSupport, Encounter* encounter);
	~Combat();
	bool DoAction(int action);
	bool RunCombat();
	void ShowGrid();
	Combatant* getUnit(int index);
	void Draw(sf::RenderWindow* window);
	int getUnitsSize();
private:
	std::vector<Combatant*> units;
	std::vector<Combatant*> enemyBack;
	std::vector<Combatant*> enemyFront;
	std::vector<Combatant*> playerFront;
	std::vector<Combatant*> playerBack;
	std::vector<Combatant*> turnOrder;
	std::vector<TileRow*> combatGrid;
	std::vector<sf::Text> combatGridText;
	sf::Font font;
	void generateTurnOrder();
	void AdvanceTurn();
	bool bValidAction = false;
	bool bValidTarget = false;
	bool bIsCombat = false;
	int turn = 0;
	CombatPhases phase = TARGET;
};


