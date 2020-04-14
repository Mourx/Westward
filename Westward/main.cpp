#pragma once
#include "Combat.h"
#include <iostream>
#include "json.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Values.h"
using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");


	cout << "A group of Enemies Approach!" << endl << endl;
	vector<Combatant*> playerMain;
	vector<Combatant*> playerSupport;
	playerMain.push_back(new Combatant(new Enemy(1),true));
	playerSupport.push_back(new Combatant(new Enemy(2),true));
	Encounter* encounter = new Encounter(1);
	Combat* combat = new Combat(playerMain,playerSupport,encounter);
	
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"));
	sf::Text textTarget;
	textTarget.setFont(font);
	textTarget.setFillColor(sf::Color::White);
	textTarget.setCharacterSize(20);
	textTarget.setPosition(300, 300);
	int targetIndex = 0;
	Combatant* targ = combat->getUnit(targetIndex);
	textTarget.setString(targ->unit->getName());
	
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					targetIndex--;
					if (targetIndex <= 0) targetIndex = 0;
					targ = combat->getUnit(targetIndex);
					textTarget.setString(targ->unit->getName());
				}
				if (event.key.code == sf::Keyboard::Right) {
					targetIndex++;
					if (targetIndex >= combat->getUnitsSize()) targetIndex = combat->getUnitsSize()-1;
					targ = combat->getUnit(targetIndex);
					textTarget.setString(targ->unit->getName());
				}
				combat->DoAction(targetIndex);
			}
		}

		window.clear();
		// add images here
		window.draw(textTarget);
		combat->Draw(&window);
		window.display();

	}

	combat->RunCombat();
	for (Combatant* c : encounter->getEnemies()) {
		//cout << "name: " << c->unit->getName() << endl;
	}
	

	getchar();
	return 0;
}