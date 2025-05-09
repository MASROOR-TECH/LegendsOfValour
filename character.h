#pragma once
#include <iostream>
#include <string>
#include "inventory.h"
using namespace std;

enum characterType {WARRIOR, MAGE, ROGUE};

class Character {
private:
	string name;
	int level, experience, health, mana, attack, defense;
	Inventory* inventory;
	characterType type;
	const int maxHealth, maxMana;
	static int playerCount;
public:
	virtual void useSpecialAbility() = 0;
	void attackEnemy(Enemy&);

	void setName(string);
	void setLevel(int);
	void setExperience(int);
	void setAttack(int);
	void setHealth(int);
	void setMana(int);
	void setDefense(int);

	string getName() const;
	int getLevel() const;
	int getExperience(int) const;
	int getAttack(int) const;
	int getHealth(int) const;
	int getMana(int) const;
	int getDefense(int) const;
};

class Warrior : public Character {
public:
	Warrior();
	void useSpecialAbility() override;
};

class Mage : public Character {
public:
	Mage();
	void useSpecialAbility() override;
};

class Rogue : public Character {
public:
	Rogue();
	void useSpecialAbility() override;
};