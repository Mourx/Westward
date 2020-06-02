#pragma once
#include <vector>
#include "Combatant.h"
#include "TileRow.h"
#include "Encounter.h"
#include "enums.h"
#include "ActionPrompt.h"
#include <SFML/Graphics.hpp>
class Combat
{
public:
	Combat(std::vector<Combatant*> playerMain, std::vector<Combatant*> playerSupport, Encounter* encounter);
	~Combat();
	bool DoAction(CombatActions action);
	bool DoAction(int target);
	void generateActions();
	bool RunCombat();
	void ShowGrid();
	Combatant* getUnit(int index);
	void Draw(sf::RenderWindow* window);
	void setCursorPosition(Combatant* targ);
	void setCursorPosition(ActionPrompt* act);
	int getUnitsSize();
	void updateStrings(Combatant* targ);
	CombatPhases CheckCombatOver(CombatPhases currentPhase);
	void Attack(Combatant* user, Combatant* target);
	std::vector<Combatant*> getUnitList(bool bPlayer);
	CombatPhases getPhase();
	ActionPrompt* getAction(int actionIndex);
	int getActionAmount();
private:
	void changePhase(CombatPhases p);
	std::vector<Combatant*> units;
	std::vector<Combatant*> enemyBack;
	std::vector<Combatant*> enemyFront;
	std::vector<Combatant*> playerFront;
	std::vector<Combatant*> playerBack;
	std::vector<Combatant*> turnOrder;
	std::vector<TileRow*> combatGrid;
	std::vector<sf::Text> combatGridText;
	std::vector<sf::Sprite*> combatGridIcons;
	sf::Font font;
	sf::Texture playerSquare;
	sf::Texture enemySquare;
	sf::Texture cursorTexture;
	sf::Sprite cursorTarget;
	sf::Sprite cursorAction;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Texture combatTexture;
	sf::Sprite combat;
	sf::Texture dialogTexture;
	sf::Sprite dialog;
	sf::Texture statsTexture;
	sf::Sprite stats;
	sf::Texture heartTexture;
	sf::Sprite heart;
	sf::Texture swordTexture;
	sf::Sprite sword;
	sf::Texture shieldTexture;
	sf::Sprite shield;
	sf::Text inspectHealth;
	sf::Text inspectDamage;
	sf::Text inspectDefense;
	sf::Text inspectName;
	Combatant* target;
	vector<ActionPrompt*> availableActions;
	void generateTurnOrder();
	void AdvanceTurn();
	bool bValidAction = false;
	bool bValidTarget = false;
	bool bIsCombat = false;
	int turn = 0;
	int totalEnemies = 0;
	int totalPlayers = 0;
	int deadEnemies = 0;
	int deadPlayers = 0;
	CombatPhases phase = ACTION;
};


