#pragma once
#include <iostream>
#include <string>
#include "enemy.h"
using namespace std;

enum characterType { WARRIOR = 1, MAGE, ROGUE };
class Enemy;
class Character {
private:
	string name;
	int level, experience, health, mana, attack, defense, points;
	characterType type;
	const int maxHealth = 100, minHealth = 0, maxMana = 100, minMana = 0;
	static int playerCount;
public:
	Character();

	virtual void useSpecialAbility() = 0;
	void attackEnemy(Enemy&);

	void setName(string);
	void setLevel(int);
	void setExperience(int);
	void setAttack(int);
	void setHealth(int);
	void setMana(int);
	void setDefense(int);
	void setCharacterType(characterType);

	string getName() const;
	int getLevel() const;
	int getExperience() const;
	int getAttack() const;
	int getHealth() const;
	int getMana() const;
	int getDefense() const;
	const int getCharacterType() const;
};

class Warrior : public Character {
public:
	Warrior(string);
	void useSpecialAbility() override;
};

class Mage : public Character {
public:
	Mage(string);
	void useSpecialAbility() override;
};

class Rogue : public Character {
public:
	Rogue(string);
	void useSpecialAbility() override;
};