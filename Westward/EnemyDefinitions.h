#pragma once
#include "json.h"
#include <iostream>
#include <fstream>
using namespace Json;
using namespace std;
class VirtualEnemy {
public:
	VirtualEnemy() {

	}
	~VirtualEnemy() {

	}
	
protected:
	int health;
	int damage;
	int speed;
	int level;
	string name;
	float challengeValue;
	bool bFrontLine;
	bool bHasSpells;
};

class Enemy : VirtualEnemy {
public:
	Enemy(int EnemyType) {
		ifstream monStream("enemies.json");

		CharReaderBuilder reader;
		Value obj;
		string errs;

		if (parseFromStream(reader, monStream, &obj, &errs)) {
			//cout << errs << endl;
		}

		name.assign(obj[EnemyType]["name"].asString());
		health = obj[EnemyType]["health"].asInt();
		damage = obj[EnemyType]["damage"].asInt();
		speed = obj[EnemyType]["speed"].asInt();
		level = obj[EnemyType]["level"].asInt();
		challengeValue = obj[EnemyType]["challengeValue"].asInt();
		bFrontLine = obj[EnemyType]["frontLine"].asBool();
		bHasSpells = obj[EnemyType]["hasSpells"].asBool();
		//spellList = obj[EnemyType]["spellList"].asInt();
	}
	int getHealth() {
		return health;
	}
	int getDamage() {
		return damage;
	}
	int getSpeed() {
		return speed;
	}
	int getLevel() {
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

};

