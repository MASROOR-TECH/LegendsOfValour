#include "GameManager.h"
#pragma once
#include <string>
using namespace std;
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
        case '1': player = new Mage(name+"_Mage");
            break;
        case '2': player = new Warrior(name+"_Warrior");
            break;
        case '3': player = new Rogue(name+"_Rouge");
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
        if (isGameOver) {
            cout << "\nGame Over! You have died.\n";
            isRunning = false;
        }
    }

}



void GameManager::showPlayerStats() const {
    cout  << "========= PLAYER STATS =========" << "\n";
    cout <<  "Name:          "  << player->getName() << '\n';
    cout <<  "Level:         "  << player->getLevel() << '\n';
    cout <<  "Health:        "  << player->getHealth() << '\n';
    cout <<  "Mana:          "  << player->getMana() << '\n';
    cout <<  "Attack Power:  "  << player->getAttack() << '\n';
    cout <<  "Defense:       "  << player->getDefense() << '\n';
    cout <<  "Experience:    "  << player->getExperience() << '\n';
    cout << "================================" << "\n";
}

void GameManager::openInventory() {
    cout << "Inventory Displayed: " << endl;
    inventory->showInventory();
    cout << "1. Use Item\n2. Discard Item\n3. Exit\n";
    char choice = _getch(); 
    switch (choice) {
    case '1': useItem(); break;
    case '2': discardItem(); break;  //This function is not use due my fellow not make this function in Inventory but i can fix it
    case '3': return;
    default: cout << "Invalid choice.\n"; break;
    }
}
void GameManager::useItem() {
    cout << "\nEnter the name of the item you want to use: ";
    string useitem;
    cin.ignore();
    getline(cin, useitem);

    Item* item = inventory->getItem(useitem); // You need to define this method
    if (item) {
        item->useItem();  // Polymorphic call
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

    bool success = inventory->removeItem(itemName); 
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

    if (randomChance < 25) { // 25% chance for rare
        enemy->setName(name);
        enemy->setHealth(150);
        enemy->setAttack(40);
        enemy->setDefense(25);
        enemy->setRare(true);
        cout << "\nA rare enemy appeared: " << enemy->getName() << "!\n";
    }
    else {
        enemy->setName(name);
        enemy->setHealth(80);
        enemy->setAttack(20);
        enemy->setDefense(10);
        enemy->setRare(false);
        cout << "\nAn enemy appeared: " << enemy->getName() << ".\n";
    }
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
    cout << "You earn " << xp << "Experience" << "\n";
    player->setExperience(xp);
}

void GameManager::processTurn(Enemy& enemy) {
    char choice;
    cout << "\nYour Turn:\n";
    cout << "1. Attack\n";
    cout << "2. Use Special Ability (40 Mana)\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == '1') {
        player->attackEnemy(enemy);
    }
    else if (choice == '2') {
        player->useSpecialAbility(); // Polymorphic call
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
        Enemy enemy = generateRandomEnemy((i == 1 ? "Shadowroot Panther" : "Forest Howler"));  // Already handles normal/rare
        startCombat(enemy);
        if (isGameOver) return;
    }

    // Optional: Placeholder for Forest Boss
    // Enemy forestBoss = generateForestBoss();
    // startCombat(forestBoss);

    // ====== CAVE PHASE ======
    Arena cave("Echoing Caverns", CAVE, 2);
    cave.describe();

    for (int i = 1; i <= 3; ++i) {
        cout << "\nCave Encounter " << i << " of 3\n";
        Enemy enemy = generateRandomEnemy(i == 1 ? "Cave Crawler" :i == 2 ? "Stoneback Beetle" :"Lurking Ghoul");
        startCombat(enemy);
        if (isGameOver) return;
    }

    // Optional: Placeholder for Cave Boss
    // Enemy caveBoss = generateCaveBoss();
    // startCombat(caveBoss);

    // ====== TOWN PHASE ======
    Arena town("Forsaken Town", TOWN, 3);
    town.describe();

    cout << "\nTown Encounter 1 of 1\n"; 
    Enemy enemy = generateRandomEnemy("Ghost of the Mayor");
    startCombat(enemy);
    if (isGameOver) return;

    // Optional: Placeholder for Town Boss
    // Enemy townBoss = generateTownBoss();
    // startCombat(townBoss);

    cout << "\nYou have cleared all areas. Prepare for boss battles!\n";
}

//function to generate random loot
//Item* GameManager::generateRandomLoot() {
//    int roll = rand() % 4;
//    switch (roll) {
//    case 0: return new Potion("Healing Elixir", 1);
//    case 1: return new Weapon("Bronze Sword", 10);
//    case 2: return new Armor("Wooden Shield", 8);
//    case 3: return new Collectable("Ancient Coin", 1);
//    default: return nullptr;
//    }
//}


