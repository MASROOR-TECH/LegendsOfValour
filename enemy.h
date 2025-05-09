#pragma once
#include <iostream>
#include <string>
using namespace std;

class Enemy {
private:
	string name;
	int health, attack, defense;
	const int maxHealth;
public:
	void setName(string);
	void setHealth(int);
	void setAttack(int);

	string getName() const;
	int getHealth() const;
	int getAttack() const;

	void attackPlayer(Character&);
};

class Boss : public Enemy {
public:
	void useSepcialAbility();
	void dodgeAttack();
};