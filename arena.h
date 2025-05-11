#pragma once
#include <iostream>
#include <string>
#include "enemy.h"
#include "inventory.h"
#include "character.h"
using namespace std;

enum arenaType{FOREST ,CAVE, TOWN};

class Arena {
private:
    string name;              
    arenaType type;            // FOREST, CAVE, TOWN
    static float difficultyLevel;
public:
    Arena();                   // Default constructor
    Arena(string name, arenaType type, int difficulty);

    // Setters
    void setName(const string&);
    void setType(arenaType);
    void setDifficulty(int);

    // Getters
    string getName() const;
    arenaType getType() const;
    int getDifficulty() const;

    void describe() const;     
};
