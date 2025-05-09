#pragma once
#include <iostream>
#include <string>
using namespace std;

enum itemType {WEAPON, ARMOR, POTION, COLLECTABLE};

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

class Weapon : virtual public Item {
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

class Potion : virtual public Item {
private:
	enum potionType {HEAL, ATTACK, DEFENSE};
	potionType type;
	const int potionPower;
	int numOfPotions;
public:
	Potion();

	const int getPotionType() const;
	void setPotionType(const int);

	void useItem() override;
};

class Collectable : virtual public Item {
public:
	Collectable();
	void useItem() override;
};

class Inventory : public Item {
private:
	Item* weapons = new Weapon;
	Item* potions = new Potion[3];
	Item* armors = new Armor;
	Item* collectables = new Collectable;
	const int inventorySize;
public:
	Inventory();
	int getInventorySize() const;
	~Inventory();
};