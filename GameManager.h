#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include"inventory.h"
#include"character.h"
#include"arena.h"
#include"enemy.h"
using namespace std;
class GameManager
{
    Character* player;
    Inventory* inventory;
public:
    // Main Game Control
    void mainMenu();              // Show main menu: New Game, Load Game, Quit
    void startGame();            // Initialize new game
    void loadGame();             // Load existing game from file
   void runGameLoop();          // Main in-game loop

  
   // // Exploration and Events
   void exploreMap();           // Move to new area and check for events
   // void handleRandomEncounter();// Random chance of enemy or treasure

   // // Combat
   //// void startCombat(Enemy& enemy);    // Turn-based battle system
   // void processTurn();                // Handle one turn of combat
   // void useSkillMenu();               // Player selects and uses a skill

   // // Player & Inventory
    void showPlayerStats() const;      // Display player info
    void openInventory();              // View and manage items
    void useItem();                    // Use item from inventory
    void equipItem();                  // Equip weapon or armor
    void discardItem();
   // // Save & Exit
    void saveGame() const;             // Write game state to file
    void quitGame();                   // Exit with optional save
    bool isGameOver() const;           // Check end condition

   // // Optional Features
   // void levelUpPlayer();              // Level up logic
   // void battleHistoryLog() const;     // View past battles
   // void finalScoreReport() const;     // Display end-of-game stats

};

