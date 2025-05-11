#include "arena.h"

float Arena::difficultyLevel = 0.0;

Arena::Arena(){}

Arena::Arena(string name, arenaType type, int difficulty):name(name),type(type), difficultyLevel(difficulty){}

void Arena::setName(const string& n) {
    name = n;
}

void Arena::setType(arenaType t) { 
    type = t; 
}

void Arena::setDifficulty(int d) { 
    difficultyLevel = d; 
}

string Arena::getName() const { 
    return name; 
}

arenaType Arena::getType() const { 
    return type; 
}

int Arena::getDifficulty() const { 
    return difficultyLevel; 
}

void Arena::describe() const {
    if (type == FOREST) {
        cout << "\nYou enter the forest — a wild and unpredictable place.\n"
            << "Thick trees block your view, and hostile creatures stalk the underbrush.\n"
            << "You may encounter normal enemies, rare beasts, or even a forest guardian boss.\n";
    }
    else if (type == CAVE) {
        cout << "\nYou venture into a deep, twisting cave system.\n"
            << "Echoes of unknown creatures bounce off the walls.\n"
            << "Watch for rare enemies and powerful subterranean bosses lurking in the shadows.\n";
    }
    else if (type == TOWN) {
        cout << "\nYou step into a corrupted town overtaken by dark forces.\n"
            << "Once a place of peace, it now hides enemies behind broken buildings\n"
            << "— and perhaps a fallen hero turned boss.\n";
    }
}
