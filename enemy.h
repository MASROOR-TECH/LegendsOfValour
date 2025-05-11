#pragma once
#include <iostream>
#include <string>
#include "character.h"
using namespace std;

//class Character;

class Enemy {
private:
	string name;
	int health, attack, defense;
	const int maxHealth = 100, minHealth = 0;
	/*bool isRare;*/
public:
	Enemy(string);

	void setName(string);
	void setHealth(int);
	void setAttack(int);
	void setDefense(int);
	void setRare(bool);
	string getName() const;
	int getHealth() const;
	int getAttack() const;
	int getDefense() const;
	bool getRare() const;
	void attackPlayer(Character&);
};