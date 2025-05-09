#include <iostream>
#include <string>
#include "enemy.h"
#include "character.h"
using namespace std;

Enemy::Enemy(string n){
	health = 100;
	name = n;
}

void Enemy::setName(string n) {
	name = n;
}
void Enemy::setHealth(int h) {
	if (h >= 0 && h <= 100) {
		health = h;
	}
	else {
		cout << "Invalid Enemy Health" << endl;
	}
}
void Enemy::setAttack(int a) {
	if (a >= 0 && a <= 100) {
		attack = a;
	}
	else {
		cout << "Invalid Enemy Attack" << endl;
	}
}
void Enemy::setDefense(int d) {
	if (d >= 0 && d <= 100) {
		defense = d;
	}
	else {
		cout << "Invalid Enemy Defense" << endl;
	}
}

string Enemy::getName() const {
	return name;
}
int Enemy::getHealth() const {
	return health;
}
int Enemy::getAttack() const {
	return attack;
}
int Enemy::getDefense() const {
	return defense;
}

void Enemy::attackPlayer(Character& objCharacter) {
	if (objCharacter.getDefense() >= attack) {
		cout << "\n0 damage dealt to " << objCharacter.getName() << " by " << name << endl;
	}
	else {
		objCharacter.setHealth(objCharacter.getHealth() - (attack - objCharacter.getDefense()));
		cout << endl << (attack - objCharacter.getDefense()) << " damage dealt to " << objCharacter.getName() << " by " << name << endl;
	}
}