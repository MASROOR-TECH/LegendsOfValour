#pragma once
#include <iostream>
#include <string>
#include"character.h"
#include<vector>
using namespace std;

enum itemType { WEAPON, ARMOR, POTION, COLLECTABLE };
enum potionType { HEAL = 1, ATTACK, REVIVE };
enum weaponType { SWORD = 1, AXE, WAND };
enum armorType { BRONZE = 1, GOLD, DIAMOND };

class Item {
private:
	string name;
	itemType type;
	int value, size;
public:
	virtual void useItem(Character& player) = 0;
	void setName(string);
	void setValue(int);
	void setSize(int);

	string getName() const;
	int getValue() const;
	int getSize() const;
};

class Weapon : public Item {
private:
	 int attack;
	 weaponType type;
public:
	Weapon(){}
	Weapon(weaponType);
	void useItem(Character& player) override;

};

class Armor : public Item {
private:
	 int defense;
	 armorType type;
public:
	Armor(){}
	Armor(armorType);
	void useItem(Character& player) override;
};

class Potion : public Item {
private:
	potionType type;
	int potionPower;
	int numOfPotions;
	const int maxPotions = 3;
public:
	Potion(){}
	Potion(potionType);
	const int getPotionType() const;
	void setPotionType(int);

	void useItem(Character& player) override;
};

class Collectable : public Item {
public:
	Collectable(){}
};

class Inventory {
private:
	vector<Item*>item;
	int inventorySize;
	const int maxInventorySize = 80;
public:
	Inventory();
	bool addItem(Item* item);
	Item* getItem(string name);
	bool removeItem(string itemName);
	void showInventory() const;
	int getInventorySize() const;
	~Inventory();
};