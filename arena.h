#pragma once
#include <iostream>
#include <string>
#include "enemy.h"
#include "inventory.h"
#include "character.h"
using namespace std;
enum ArenaType{FOREST,CAVE,TOWN};
class Arena {
private:
    string name;              
    ArenaType type;            // FOREST, CAVE, TOWN
    int difficultyLevel;       // Affects enemy stats or rarity chances
public:
    Arena();                   // Default constructor
    Arena(string name, ArenaType type, int difficulty);

    // Setters
    void setName(const string&);
    void setType(ArenaType);
    void setDifficulty(int);

    // Getters
    string getName() const;
    ArenaType getType() const;
    int getDifficulty() const;

    void describe() const;     
};
