#pragma once
#include <iostream>
#include <string>
#include<vector>
using namespace std;

enum itemType { WEAPON, ARMOR, POTION, COLLECTABLE };

class Item {
private:
	string name;
	itemType type;
	int value, size;
public:
	virtual void useItem() = 0;

	void setName(string);
	void setValue(int);
	void setSize(int);

	string getName() const;
	int getValue() const;
	int getSize() const;
};

class Weapon : public Item {
private:
	const int attack;
public:
	Weapon();
	void useItem() override;
};

class Armor : virtual public Item {
private:
	const int defense;
public:
	Armor();
	void useItem() override;
};

class Potion : public Item {
private:
	enum potionType { HEAL, ATTACK, DEFENSE };
	potionType type;
	const int potionPower;
	int numOfPotions;
public:
	Potion();

	const int getPotionType() const;
	void setPotionType(const int);

	void useItem() override;
};

class Collectable : public Item {
public:
	Collectable();
	void useItem() override;
};
//i change this
class Inventory {
private:
	vector<Item*>item;
	const int inventorySize;
public:
	Inventory();
	bool addItem(Item* item);
	Item* getItem(string name);
	bool removeItem(string itemName);
	void showInventory() const;
	int getInventorySize() const;
	~Inventory();
};
