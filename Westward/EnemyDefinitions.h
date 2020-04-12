#pragma once
#include <json.h>
class VirtualEnemy {
public:
	VirtualEnemy() {

	}
	~VirtualEnemy() {

	}
	int getHealth() {
		return health;
	}
	int getDamage() {
		return damage;
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
	
protected:
	int health;
	int damage;
	int level;
	float challengeValue;
	bool bFrontLine;
	bool bHasSpells;
};

class Enemy : VirtualEnemy {
	Enemy(int EnemyType) {
		health = 20;
		damage = 10;
		level = 1;
		challengeValue = 0.25;
		bFrontLine = true;
		bHasSpells = false;
	}
};

