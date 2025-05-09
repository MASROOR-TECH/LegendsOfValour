#include <iostream>
#include <string>
#include "character.h"
#include "inventory.h"
#include "enemy.h"
using namespace std;

//Character Class
int Character::playerCount;

Character::Character() {
	++playerCount;
	health = 100;
	mana = 50;
	level = 1;
	experience = 0;
}

void Character::attackEnemy(Enemy& objEnemy) {
	if (objEnemy.getDefense() >= attack) {
		cout << "\n0 damage dealt to " << objEnemy.getName() << " by " << name << endl;
	}
	else {
		objEnemy.setHealth(objEnemy.getHealth() - (attack - objEnemy.getDefense()));
		cout << endl << (attack - objEnemy.getDefense()) << " damage dealt to " << objEnemy.getName() << " by " << name << endl;
	}
}

void Character::setName(string n) {
	name = n;
}
void Character::setLevel(int l) {
	if (l > 0 && l <= 10) {
		level = l;
	}
	else {
		cout << "\nInvalid Player Level" << endl;
		return;
	}
}
void Character::setExperience(int exp) {
	if (exp >= 0 && exp <= 100) {
		if (experience + exp >= 100) {
			setLevel(++level);
			experience = (experience + exp) - 100;
		}
		else {
			experience += exp;
		}
	}
	else {
		cout << "\nInvalid Player Experience" << endl;
		return;
	}
}
void Character::setAttack(int a) {
	if (a >= 0 && a <= 100) {
		attack = a;
	}
	else {
		cout << "\nInvalid Player Attack" << endl;
		return;
	}
}
void Character::setHealth(int h) {
	if (h >= 0 && h <= 100) {
		health = h;
	}
	else {
		cout << "\nInvalid Player Health" << endl;
		return;
	}
}
void Character::setMana(int m) {
	if (m >= 0 && m <= 100) {
		mana = m;
	}
	else {
		cout << "\nInvalid Player Mana" << endl;
		return;
	}
}
void Character::setDefense(int d) {
	if (d >= 0 && d <= 100) {
		defense = d;
	}
	else {
		cout << "\nInvalid Player Defense" << endl;
		return;
	}
}
void Character::setCharacterType(characterType t) {
	if (t == 1) {
		type = WARRIOR;
	}
	else if (t == 2) {
		type = MAGE;
	}
	else if (t == 3) {
		type = ROGUE;
	}
}

string Character::getName() const {
	return name;
}
int Character::getLevel() const {
	return level;
}
int Character::getExperience() const {
	return experience;
}
int Character::getAttack() const {
	return attack;
}
int Character::getHealth() const {
	return health;
}
int Character::getMana() const {
	return mana;
}
int Character::getDefense() const {
	return defense;
}
const int Character::getCharacterType() const {
	if (type == WARRIOR) {
		return 1;
	}
	else if (type == MAGE) {
		return 2;
	}
	else if (type == ROGUE) {
		return 3;
	}
}

//Warrior Class
Warrior::Warrior(string n) : Character() {
	setCharacterType(WARRIOR);
	setAttack(27);
	setDefense(20);
	setName(n);
}
void Warrior::useSpecialAbility() {
	if (getMana() >= 40) {
		setDefense(getDefense() + 15);
		setMana(getMana() - 40);
		cout << "Special ability used by " << getName() << endl;
	}
}

//Mage Class
Mage::Mage(string n) : Character() {
	setCharacterType(MAGE);
	setAttack(22);
	setDefense(26);
	setName(n);
}
void Mage::useSpecialAbility() {
	if (getMana() >= 40) {
		setAttack(getAttack() + 15);
		setMana(getMana() - 40);
		cout << "Special ability used by " << getName() << endl;
	}
}

//Rogue Class
Rogue::Rogue(string n) : Character() {
	setCharacterType(ROGUE);
	setAttack(25);
	setDefense(25);
	setName(n);
}
void Rogue::useSpecialAbility() {
	if (getMana() >= 40) {
		setAttack(getAttack() + 8);
		setDefense(getDefense() + 8);
		setMana(getMana() - 40);
		cout << "Special ability used by " << getName() << endl;
	}
}