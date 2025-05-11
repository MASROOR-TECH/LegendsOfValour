#include "GameManager.h"
#pragma once
#include <string>
using namespace std;
void GameManager::mainMenu() {
    char choice;
    do {
        cout << "1. Start New Game\n";
        cout << "2. Load Saved Game\n";
        cout << "3. Quit\n";
        choice = _getch();
        switch (choice)
        {
        case '1':
            startGame();
            runGameLoop();
            break;
        case '2':
            loadGame();
            runGameLoop();
            break;
        case '3':break;
        default:
            cout << "Invalid Input! Try Again\n";
            break;
        }
    } while (choice != '3');
}


void GameManager::startGame() {
    char choice;
    do {
        cout << "\nSelect Character: \n1.Mage 2.Warrior 3.Rogue: ";
        choice = _getch();
        switch (choice)
        {//The Default player stats are given later
        case '1': player = new Mage(name);
            break;
        case '2': player = new Warrior(name);
            break;
        case '3': player = new Rogue(name);
            break;
        default:
            cout << "\nInvalid choice! Try Again\n ";
            break;
        }
    } while (choice != '1' && choice != '2' && choice != '3');
    cout << "\nEnter player name: ";
    string name;
    getline(cin, name);

    // Starting info
    cout << "\nWelcome " << name << "!\n";
    cout << "Your journey in Legends of Valor begins...\n";

    //Inventory logic is implement at this line later
    //Some default things is given to user 
    //Give some default item
    Item* armor = new Armor();
    armor->setName("Wooden Armor");
    /*armor->setSize(2);
    armor->setValue(15);*/
    inventory.addItem(armor);

    Item* sword = new Weapon();
    sword->setName("Wooden Sword");
    /*sword->setSize(1);
    sword->setValue(10);*/
    inventory.addItem(sword);

    Potion* healPotion = new Potion();
    healPotion->setName("Healing Potion");
    /*healPotion->setSize(1);
    healPotion->setValue(5);*/
    healPotion->setPotionType(0); // 0 = HEAL
    inventory.addItem(healPotion);

    
}


void GameManager::runGameLoop() {
    system("cls");
    bool isRunning = true;
    char choice;

    while (isRunning) {
        /*cout << "\n========== GAME MENU ==========\n";*/
        cout << "1. Explore Map\n";
        cout << "2. View Player Stats\n";
        cout << "3. Open Inventory\n";
        cout << "4. Shop Items\n";
        cout << "5. Save Game\n";
        cout << "6. Quit Game\n";
        cout << "Enter your choice: ";
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
            buyItem();
            break;
        case '5':
            saveGame();
            break;
        case '6':
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
        if (isGameOver()) {
            cout << "\nGame Over! You have died.\n";
            isRunning = false;
        }
    }

}



void GameManager::showPlayerStats() const {
    cout  << "\n          PLAYER STATS " << "\n";
    cout <<  "Name: "  << player->getName() << '\n';
    cout <<  "Level: "  << player->getLevel() << '\n';
    cout <<  "Health: "  << player->getHealth() << '\n';
    cout <<  "Mana: "  << player->getMana() << '\n';
    cout <<  "Attack Power: "  << player->getAttack() << '\n';
    cout <<  "Defense: "  << player->getDefense() << '\n';
    cout <<  "Experience: "  << player->getExperience() << '\n';
    cout << endl;
}

void GameManager::openInventory() {
    cout << "\n          PLAYER INVENTORY" << endl;
    inventory.showInventory();
    
    /*cout << "1. Use Item\n2. Discard Item\n3. Exit\n";
    This line should be like this:
    cout << "1. Add Item\n2. Discard Item\n3. Exit\n";*/

    char choice = _getch(); 
    switch (choice) {
    /*case '1': useItem(); break;
    addItem() should be used instead*/
    case '2': 
        discardItem(); 
        break;  //This function is not use due my fellow not make this function in Inventory but i can fix it
    case '3': 
        return;
    default: 
        cout << "Invalid choice.\n"; 
        break;
    }
}
void GameManager::useItem() {
    cout << "\nEnter the name of the item you want to use: ";
    string useitem;
    cin.ignore();
    getline(cin, useitem);

    Item* item = inventory.getItem(useitem); // You need to define this method
    if (item) {
        item->useItem(*player);  // Polymorphic call
        cout << "Item used successfully!\n";
    }
    else {
        cout << "Item not found in inventory.\n";
    }
}

void GameManager::discardItem() {
    cout << "\nEnter the name of the item you want to discard: ";
    string itemName;
    cin.ignore();
    getline(cin, itemName);

    bool success = inventory.removeItem(itemName); 
    if (success) {
        cout << "Item discarded successfully.\n";
    }
    else {
        cout << "Item not found or cannot be discarded.\n";
    }
}


//Function to check game is over or not
bool GameManager::isGameOver() const { if (player->getHealth() <= 0 ) { return true;} else { return false; } }
//Function to load game 
void GameManager::loadGame() {
    cout << "Enter name of file (without .txt): ";
    string fileName;
    cin >> fileName;
    fileName += ".txt";

    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << endl;
        return;
    }

    string name, classType;
    int level, xp, health, mana, attack, defense;

    getline(file, name);
    getline(file, classType);
    file >> level >> xp >> health >> mana >> attack >> defense;
    characterType type;
    // Create appropriate character
    if (classType == "Warrior") {
        player = new Warrior(name+"_Warrior");
        player->setCharacterType(WARRIOR);
    }
    else if (classType == "Mage") {
        player = new Mage(name+"_Mage");
        player->setCharacterType(MAGE);
    }
    else if (classType == "Rogue") {
        player = new Rogue(name+"_Rouge");
        player->setCharacterType(ROGUE);
    }
    else {
        cout << "Unknown class type in save file.\n";
        return;
    }

    // Set player attributes
    player->setLevel(level);
    player->setExperience(xp);
    player->setHealth(health);
    player->setMana(mana);
    player->setAttack(attack);
    player->setDefense(defense);
   
    file.close();
    cout << "Game loaded successfully!\n";

    runGameLoop(); // Start the game
}

//Function to save the game 
void GameManager::saveGame() const {
    cout << "Enter name of file to save (without .txt): ";
    string fileName;
    cin >> fileName;
    fileName += ".txt";

    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Error creating file: " << fileName << endl;
        return;
    }

    // Save basic player data
    file << player->getName() << '\n';

    // Assume you have a getType() that returns "Warrior", "Mage", or "Rogue"
    int typeCode = player->getCharacterType(); // returns 1, 2, or 3

    if (typeCode == 1) {
        file << "Warrior" << '\n';
    }
    else if (typeCode == 2) {
        file << "Mage" << '\n';
    }
    else if (typeCode == 3) {
        file << "Rogue" << '\n'; // Fixed spelling here
    }
    else {
        file << "Unknown" << '\n';
    }

    file << player->getLevel() << ' '
        << player->getExperience() << ' '
        << player->getHealth() << ' '
        << player->getMana() << ' '
        << player->getAttack() << ' '
        << player->getDefense() << '\n';

    file.close();
    cout << "Game saved successfully as " << fileName << '\n';
}
//Quit game function 
void GameManager::quitGame() {
    char choice;
    cout << "\nDo you want to save your game before quitting? (y/n): ";
    choice = _getch();

    if (choice == 'y' || choice == 'Y') {
        saveGame();
    }

    cout << "\nThank you for playing Legends of Valor!\n";
    cout << "Goodbye, brave hero!\n";
}

//Function to generate random enemy
Enemy GameManager::generateRandomEnemy(string name) {
    Enemy* enemy;
    int randomChance = rand() % 100; // 0–99
    enemy = new Enemy("");
    if (randomChance < 25) { // 25% chance for rare
        enemy->setName(name);
        enemy->setHealth(70);
        enemy->setAttack(5);
        enemy->setDefense(3);
        enemy->setRare(true);
        cout << "\nA rare enemy appeared: " << enemy->getName() << "!\n";
    }
    else {
        enemy->setName(name);
        enemy->setHealth(90);
        enemy->setAttack(10);
        enemy->setDefense(7);
        enemy->setRare(false);
        cout << "\nAn enemy appeared: " << enemy->getName() << ".\n";
    }
    cout << "\n========= ENEMY STATS =========" << "\n";
    cout << "Name:          " << enemy->getName() << '\n';
    cout << "Health:        " << enemy->getHealth() << '\n';
    cout << "Attack Power:  " << enemy->getAttack() << '\n';
    cout << "Defense:       " << enemy->getDefense() << '\n';
    cout << "Type:          " << (enemy->getRare() ? "Rare" : "Normal") << '\n';
    cout << "================================\n";
    return *enemy;
}

//Function to start combat b/w enemy and player

void GameManager::startCombat(Enemy& enemy) {
    int xp = (enemy.getAttack() + enemy.getDefense() + enemy.getHealth()) / (2 * player->getLevel());
    if (enemy.getRare()) { xp *= 1.5; }
    cout << "\nCombat Started with " << (enemy.getRare() ? "Rare Enemy: " : "Enemy: ") << enemy.getName() << " \n";

    // Loop until one of them dies
    while (player->getHealth() > 0 && enemy.getHealth() > 0) {
        processTurn(enemy); // One full round: player + enemy
    }

    if (isGameOver()) {
        cout << "\nYou were defeated by " << enemy.getName() << "!\n";
    }
    else if (enemy.getHealth() <= 0) {
        cout << "\nYou defeated " << enemy.getName() << "!\n";
    }
    cout << "You earn " << xp << " Experience" << "\n";
    player->setExperience(xp);
}

void GameManager::processTurn(Enemy& enemy) {
    char choice;
    cout << "\nYour Turn:\n";
    cout << "1. Attack\n";
    cout << "2. Use Special Ability (40 Mana)\n";
    cout << "3. Open Inventory\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == '1') {
        player->attackEnemy(enemy);
    }
    else if (choice == '2') {
        player->useSpecialAbility(); // Polymorphic call
    }
    else if (choice == '3') {
        openInventory();
    }
    else {
        cout << "Invalid input. Skipping turn.\n";
    }

    // Enemy Turn (if still alive)
    if (enemy.getHealth() > 0) {
        enemy.attackPlayer(*player);
    }

    cout << "\nPlayer HP: " << player->getHealth() << ", Mana: " << player->getMana() << endl;
    cout << "Enemy HP: " << enemy.getHealth() << endl;
}


void GameManager::exploreMap() {
    // ====== FOREST PHASE ======
    Arena forest("Darkwood Forest", FOREST, 1);
    forest.describe();

    for (int i = 1; i <= 2; ++i) {
        cout << "\nForest Encounter " << i << " of 2\n";
        Enemy enemy = generateRandomEnemy(i == 1 ? "Shadowroot Panther" : "Forest Howler");
        startCombat(enemy);
        if (isGameOver()) 
            return;

        // Reward logic
        player->setHealth(player->getHealth() + 30);
        cout << "You recovered 30 health after the battle.\n";

        Item* loot = generateRandomLoot();
        inventory.addItem(loot);
        cout << "You found: " << loot->getName() << "\n";
    }

    // Forest Boss
    cout << "\nForest Boss Encounter: Verdant Warden\n";
    Enemy forestBoss = generateBoss("Verdant Warden", 100, 20, 10);
    startCombat(forestBoss);
    if (isGameOver()) return;

    inventory.addItem(new Weapon()); // give something strong
    cout << "You received a reward: Iron Sword!\n";

    // ====== CAVE PHASE ======
    Arena cave("Echoing Caverns", CAVE, 2);
    cave.describe();

    for (int i = 1; i <= 3; ++i) {
        cout << "\nCave Encounter " << i << " of 3\n";
        Enemy enemy = generateRandomEnemy(i == 1 ? "Cave Crawler" : i == 2 ? "Stoneback Beetle" : "Lurking Ghoul");
        startCombat(enemy);
        if (isGameOver()) return;

        if (i == 2 || i == 3) {
            player->setHealth(player->getHealth() + 40);
            cout << "You recovered 40 health after the battle.\n";
        }

        inventory.addItem(generateRandomLoot());
    }

    // Cave Boss
    cout << "\nCave Boss Encounter: Crystal Titan\n";
    Enemy caveBoss = generateBoss("Crystal Titan", 120, 25, 15);
    startCombat(caveBoss);
    if (isGameOver()) return;

    inventory.addItem(new Armor());
    cout << "You received a reward: Iron Armor!\n";

    // ====== TOWN PHASE ======
    Arena town("Forsaken Town", TOWN, 3);
    town.describe();

    cout << "\nTown Encounter 1 of 1\n";
    Enemy townEnemy = generateRandomEnemy("Ghost of the Mayor");
    startCombat(townEnemy);
    if (isGameOver()) return;

    player->setHealth(player->getHealth() + 50);
    inventory.addItem(generateRandomLoot());

    // Town Boss
    cout << "\nTown Boss Encounter: The Fallen Hero\n";
    Enemy townBoss = generateBoss("The Fallen Hero", 120, 30, 20);
    startCombat(townBoss);
    if (isGameOver()) return;

    // Final Boss
    cout << "\nFinal Boss: The Eternal King\n";
    Enemy finalBoss = generateBoss("The Eternal King", 150, 35, 25);
    startCombat(finalBoss);
    if (isGameOver()) return;

    cout << "\nCongratulations! You have completed Legends of Valor!\n";
}

//function to generate random loot
Item* GameManager::generateRandomLoot() {
    int roll = rand() % 3; // Randomly select an item type
    switch (roll) {
    case 0: // Generate a Potion
        return new Potion("Healing Potion", 5, 1, 0, 20, 1); // Name, Value, Size, Type (0 = HEAL), Power, Quantity
    case 1: // Generate a Weapon
        return new Weapon("Iron Sword", 50, 3, 25); // Name, Value, Size, Attack Power
    case 2: // Generate an Armor
        return new Armor("Steel Shield", 40, 5, 20); // Name, Value, Size, Defense Value
    default:
        return nullptr;
    }
}

Item* GameManager::buyItem() {
    int choice;
    do {
        cout << "\n1. Weapons" << endl
            << "2. Armors" << endl
            << "3. Potions" << endl
            << "4. Back to Main Menu" << endl
            << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int itemChoice;
            cout << "\n1. Sword" << endl
                << "2. Axe" << endl
                << "3. Wand" << endl
                << "Enter your choice: ";
            cin >> itemChoice;

            switch (itemChoice) {
            case 1:
                if (player.getPoints() >= 25) {
                    cout << "\nSword Bought!" << endl;
                    return (new Weapon(1));
                }
                else {
                    cout << "Insufficient Ponits to Buy Sword" << endl;
                }
            case 2:
                if (player.getPoints() >= 30) {
                    cout << "\nAxe Bought!" << endl;
                    return (new Weapon(2));
                }
                else {
                    cout << "Insufficient Ponits to Buy Axe" << endl;
                }
            case 3:
                if (player.getPoints() >= 20) {
                    cout << "\nWand Bought!" << endl;
                    return (new Weapon(3));
                }
                else {
                    cout << "Insufficient Ponits to Buy Wand" << endl;
                }
            default:
                cout << "Invalid Choice" << endl;
                break;
            }
        }
        case 2: {
            int itemChoice;
            cout << "\n1. Bronze Shield" << endl
                << "2. Gold Shield" << endl
                << "3. Diamond Shield" << endl
                << "Enter your choice: ";
            cin >> itemChoice;

            switch (itemChoice) {
            case 1:
                if (player.getPoints() >= 20) {
                    cout << "\nBronze Shield Bought!" << endl;
                    return (new Armor(1));
                }
                else {
                    cout << "Insufficient Ponits to Buy Armor" << endl;
                }
            case 2:
                if (player.getPoints() >= 25) {
                    cout << "\nGold Shield Bought!" << endl;
                    return (new Armor(2));
                }
                else {
                    cout << "Insufficient Ponits to Buy Armor" << endl;
                }
            case 3:
                if (player.getPoints() >= 30) {
                    cout << "\nDiamond Shield Bought!" << endl;
                    return (new Armor(3));
                }
                else {
                    cout << "Insufficient Ponits to Buy Armor" << endl;
                }
            default:
                cout << "Invalid Choice" << endl;
                break;
            }
        }
        case 3: {
            int itemChoice;
            cout << "\n1. Healing Potion" << endl
                << "2. Attack Potion" << endl
                << "3. Revival Potion" << endl
                << "Enter your choice: ";
            cin >> itemChoice;

            switch (itemChoice) {
            case 1:
                if (player.getPoints() >= 10) {
                    cout << "\nHealing Potion Bought!" << endl;
                    return (new Potion(1));
                }
                else {
                    cout << "Insufficient Ponits to Buy Potion" << endl;
                }
            case 2:
                if (player.getPoints() >= 10) {
                    cout << "\nAttack Potion Bought!" << endl;
                    return (new Potion(2));
                }
                else {
                    cout << "Insufficient Ponits to Buy Potion" << endl;
                }
            case 3:
                if (player.getPoints() >= 25) {
                    cout << "\nRevival Potion Bought!" << endl;
                    return (new Potion(3));
                }
                else {
                    cout << "Insufficient Ponits to Buy Potion" << endl;
                }
            default:
                cout << "Invalid Choice" << endl;
                break;
            }
        }
        case 4: {
            return;
        }
        default: {
            cout << "Invalid Choice" << endl;
            return;
        }
        }
    } while (choice != 4);
}


Enemy GameManager::generateBoss(const string& name, int health, int attack, int defense) {
    Enemy boss(name);
    boss.setHealth(health);
    boss.setAttack(attack);
    boss.setDefense(defense);
    boss.setRare(true); // Optional: treat boss as a rare-type enemy for XP calculation, etc.

    cout << "\nBoss Created: " << boss.getName() << "\n";
    cout << " HP: " << boss.getHealth()
        << " | ATK: " << boss.getAttack()
        << " | DEF: " << boss.getDefense() << "\n";

    return boss;
}
