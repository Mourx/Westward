#pragma once
#include "enums.h"
#include <SFML/Graphics.hpp>
class ActionPrompt
{
public:
	ActionPrompt(CombatActions a);
	~ActionPrompt();

	
	sf::Text name;
	sf::Font font;
	CombatActions getAction() { return action; };
private:
	CombatActions action;
};

