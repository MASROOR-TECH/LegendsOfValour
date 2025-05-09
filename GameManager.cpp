#include "GameManager.h"
#pragma once
#include <string>

namespace config {

    // Default Player Stats for Warrior
    const int warriorHealth = 120;
    const int warriorMana = 30;
    const int warriorAttack = 15;
    const int warriorDefense = 10;
    const int warriorLevel = 1;
    const int warriorExperience = 0;

    // Default Player Stats for Mage
    const int mageHealth = 80;
    const int mageMana = 100;
    const int mageAttack = 10;
    const int mageDefense = 5;
    const int mageLevel = 1;
    const int mageExperience = 0;

    // Default Player Stats for Rogue
    const int rogueHealth = 100;
    const int rogueMana = 50;
    const int rogueAttack = 12;
    const int rogueDefense = 8;
    const int rogueLevel = 1;
    const int rogueExperience = 0;

    // Shared Defaults
    const int maxHealth = 200;
    const int maxMana = 150;
}

void GameManager::mainMenu() {
    char choice;
    do {
        cout << "=============================\n";
        cout << "   LEGENDS OF VALOR - MENU  \n";
        cout << "=============================\n";
        cout << "1. Start New Game\n";
        cout << "2. Load Saved Game\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        choice = _getch();
        switch (choice)
        {
        case '1':
            startGame();
            //runGameloop();
            break;
        case '2':
            loadGame();
            //runGameloop();
            break;
        case '3':break;
        default:
            cout << "Invalid Input! Try Again\n";
            break;
        }
    } while (choice != '3');
}


void GameManager::startGame() {
   
    cout << "Enter player name: ";
    string name;
    getline(cin, name);
    cin.ignore();
    char choice;
    do {
        cout << "\nSelect Character: \n1.Mage 2.Warrior 3.Rogue: ";
        choice = _getch();
        switch (choice)
        {//The Default player stats is give later 
        case '1': player = new Mage(); 
            break;
        case '2': player = new Warrior();
            break;
        case '3': player = new Rogue();
            break;
        default:
            cout << "\nInvalid choice! Try Again\n ";
            break;
        }
    } while (choice != '1' && choice != '2' && choice != '3');
    // Starting info
    cout << "\nWelcome, " << name << "!\n";
    cout << "Your journey in Legends of Valor begins...\n";

    //Inventory logic is implement at this line later
    //Some default things is given to user 
    Item* item;
    //Give some default item
    Item* armor = new Armor();
    armor->setName("Worn Leather Armor");
    armor->setSize(2);
    armor->setValue(15);
    inventory->addItem(armor);

    Item* sword = new Weapon();
    sword->setName("Rusty Sword");
    sword->setSize(1);
    sword->setValue(10);
    inventory->addItem(sword);

    Potion* healPotion = new Potion();
    healPotion->setName("Small Healing Potion");
    healPotion->setSize(1);
    healPotion->setValue(5);
    healPotion->setPotionType(0); // 0 = HEAL
    inventory->addItem(healPotion);

    //Now its time to show inventory
    inventory->showInventory();
}

void GameManager::loadGame() {
    cout << "Enter name of file: ";
    string fileName;
    fileName += ".txt";
    ofstream file(fileName);
    if (!file.is_open()) {
        throw string("Error to open file");
    }
    
}

void GameManager::runGameLoop() {
    system("cls");
    bool isRunning = true;
    char choice;

    while (isRunning) {
        cout << "\n========== GAME MENU ==========\n";
        cout << "1. Explore Map\n";
        cout << "2. View Player Stats\n";
        cout << "3. Open Inventory\n";
        cout << "4. Save Game\n";
        cout << "5. Quit Game\n";
        cout << "Enter your choice (1-5): ";
        choice = _getch(); 

        switch (choice) {
        case '1':
            exploreMap();
            break;
        case '2':
            showPlayerStats();
            break;
        case '3':
            openInventory();
            break;
        case '4':
            saveGame();
            break;
        case '5':
            cout << "\nAre you sure you want to quit? (y/n): ";
            char confirm;
            confirm = _getch();
            if (confirm == 'y' || confirm == 'Y') {
                quitGame();
                isRunning = false;
            }
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
            break;
        }

        // check if player is dead or won
        if (player->getHealth() <= 0) {
            cout << "\nGame Over! You have died.\n";
            isRunning = false;
        }

        // I can also add logic to check for game completion (boss win)
    }

}



void GameManager::showPlayerStats() const {
    cout << "\033[1;36m" << "========= PLAYER STATS =========" << "\033[0m\n";

    cout << "\033[1;33m" << "Name:          " << "\033[0m" << player->getName() << '\n';
    cout << "\033[1;32m" << "Level:         " << "\033[0m" << player->getLevel() << '\n';
    cout << "\033[1;31m" << "Health:        " << "\033[0m" << player->getHealth() << '\n';
    cout << "\033[1;34m" << "Mana:          " << "\033[0m" << player->getMana() << '\n';
    cout << "\033[1;35m" << "Attack Power:  " << "\033[0m" << player->getAttack() << '\n';
    cout << "\033[1;36m" << "Defense:       " << "\033[0m" << player->getDefense() << '\n';
    cout << "\033[1;33m" << "Experience:    " << "\033[0m" << player->getExperience() << '\n';
    cout << "\033[1;36m" << "================================" << "\033[0m\n";
}

void GameManager::openInventory() {
    cout << "Inventory Displayed: " << endl;
    inventory->showInventory();
    cout << "1. Use Item\n2. Equip Item\n3. Discard Item\n4. Exit\n";
    char choice = _getch(); 
    switch (choice) {
    case '1': useItem(); break;
    case '2': equipItem(); break;
    case '3': discardItem(); break;  //This function is not use due my fellow not make this function in Inventory but i can fix it
    case '4': return;
    default: cout << "Invalid choice.\n"; break;
    }
}

void GameManager::useItem() {
    cout << "Select an item that you want to use: ";
    string useitem;
    cin >> useitem;

}
void GameManager::equipItem();
void GameManager::discardItem();
