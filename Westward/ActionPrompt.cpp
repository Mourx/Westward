#include "ActionPrompt.h"



ActionPrompt::ActionPrompt(CombatActions a) {
	if (!font.loadFromFile("arial.ttf"));
	switch (a) {
	case ATTACK:
		name.setString("Attack");
		break;
	case DEFEND:
		name.setString("Defend");
		break;
	default:
		name.setString("EMPTY_STRING");
		break;
	}
	name.setCharacterSize(16);
	name.setFont(font);
	name.setFillColor(sf::Color::Black);
	action = a;
}


ActionPrompt::~ActionPrompt() {

}