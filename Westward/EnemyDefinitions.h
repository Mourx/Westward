#pragma once
#include "json.h"
#include <iostream>
#include <fstream>
#include "enums.h"
#include "Modifier.h"
#include <SFML/Graphics.hpp>
using namespace Json;
using namespace std;

class BaseCombatant {
public:
	BaseCombatant() {

	}
	~BaseCombatant() {

	}
	
protected:
	float health;
	float damage;
	float defense;
	float speed;
	float level;
	string name;
	float challengeValue;
	bool bFrontLine;
	bool bHasSpells;
	sf::Sprite* icon = new sf::Sprite();
	sf::Texture texture;
	vector<Modifier*> mods;
	float comHealth;
	float comDefense;
	float comDamage;
	float comSpeed;
	bool bIsDead;
	float totHealthMod = 0;
	float totDamageMod = 0;
	float totSpeedMod = 0;
	float totDefenseMod = 0;
};

class CombatActor : BaseCombatant {
public:
	CombatActor(int EnemyType, bool bPlayer) {
		ifstream monStream;
		if (bPlayer) {
			monStream.open("players.json");
		}
		else {
			monStream.open("enemies.json");
		}
		CharReaderBuilder reader;
		Value obj;
		string errs;

		if (parseFromStream(reader, monStream, &obj, &errs)) {
			//cout << errs << endl;
		}

		name.assign(obj[EnemyType]["name"].asString());
		health = obj[EnemyType]["health"].asFloat();
		defense = obj[EnemyType]["defense"].asFloat();
		damage = obj[EnemyType]["damage"].asFloat();
		speed = obj[EnemyType]["speed"].asFloat();
		level = obj[EnemyType]["level"].asFloat();
		challengeValue = obj[EnemyType]["challengeValue"].asFloat();
		bFrontLine = obj[EnemyType]["frontLine"].asBool();
		bHasSpells = obj[EnemyType]["hasSpells"].asBool();
		//spellList = obj[EnemyType]["spellList"].asInt();

		if (bPlayer) {
			if (!texture.loadFromFile("playerSprites.png", sf::IntRect((EnemyType % 4) * 32, (EnemyType / 4) * 32, 32, 32))) {
				cout << "yikes" << endl;
			}
		}
		else {
			if (!texture.loadFromFile("spriteEnemies.png", sf::IntRect((EnemyType % 4) * 32, (EnemyType / 4) * 32, 32, 32))) {
				cout << "yikes" << endl;
			}
		}
		icon->setTexture(texture);
	}
	void calcStats() {
		comHealth = health * (1.0 + totHealthMod / 100.0);
		comDamage = damage * (1.0 + totHealthMod / 100.0);
		comSpeed = speed * (1.0 + totHealthMod / 100.0);
		comDefense = defense * (1.0 + totDefenseMod / 100.0);
	}
	void modifyHealth(float damage) {
		health -= damage;
		if (health <= 0) {
			health = 0;
			bIsDead = true;
		}
		cout << name << "'s health is " << health << "and they are " << bIsDead << endl;
	}
	bool checkDead() {
		return bIsDead;
	}

	float getCurrentHealth() {
		return comHealth;
	}
	float getCurrentDefense() {
		return comDefense;
	}

	float getCurrentDamage() {
		return comDamage;
	}
	float getSpeed() {
		return speed;
	}
	float getLevel() {
		return level;
	}
	float getChallengeValue() {
		return challengeValue;
	}
	bool getFrontLine() {
		return bFrontLine;
	}
	bool getHasSpells() {
		return bHasSpells;
	}
	string getName() {
		return name;
	}
	void addModifier(Modifier* m) {
		mods.push_back(m);
	}
	void tickModifiers() {
		for (int i = 0; i < mods.size();i++) {
			mods[i]->Tick();
			if (mods[i]->CheckExpire()) {
				mods.erase(mods.begin()+i);
				i--;
			}
		}
	}
	void ApplyModifiers() {
		totHealthMod = 0;
		totDamageMod = 0;
		totSpeedMod = 0;
		totDefenseMod = 0;
		for (Modifier* m : mods) {
			switch (m->getAtt()) {
			case HEALTH:
				totHealthMod += m->getValue();
				break;
			case DAMAGE:
				totDamageMod += m->getValue();
				break;
			case SPEED:
				totSpeedMod += m->getValue();
				break;
			}
		}

	}
	void setPosition(int x, int y) {
		icon->setPosition(x, y);
	}
	sf::Sprite getSprite() {
		return *icon;
	}
	sf::Vector2f getPosition() {
		return icon->getPosition();
	}
};

