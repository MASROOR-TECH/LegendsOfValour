# 🛡️ Legends of Valor

**Legends of Valor** is a turn-based, text-based RPG game built in C++ where you play as a hero exploring dangerous regions filled with enemies, loot, and boss battles. Choose your class — Warrior, Mage, or Rogue — and fight through forest, cave, and town arenas to free the land from darkness.

---

## 🎮 Features

- 🧙‍♂️ Choose from 3 unique character classes:
  - **Warrior** – High defense, melee strength
  - **Mage** – Magic-focused, high mana
  - **Rogue** – Balanced stats with agility buffs

- ⚔️ **Turn-based combat system** with:
  - Normal and rare enemies
  - Special abilities for each class
  - Random damage logic and defense calculations

- 🗺️ **Linear map progression**:
  - Explore **Forest**, **Cave**, and **Town**
  - Each area includes themed enemies and loot
  - Boss fight slots ready for future implementation

- 🎁 **Loot system**:
  - Items drop after battles or from random treasure
  - Includes Potions, Weapons, Armor, and Collectables

- 🎒 **Inventory management**:
  - Use, equip, or discard items
  - Inventory organized by item type

- 📈 **XP and Leveling**:
  - Gain XP from combat
  - Level up to increase stats and earn bonus items

---

## 📦 Code Structure

- `Character.h / .cpp` – Player classes and combat stats
- `Enemy.h / .cpp` – Enemy types and behavior
- `Inventory.h / .cpp` – Item system and loot management
- `GameManager.h / .cpp` – Core logic and game loop
- `Arena.h / .cpp` – Area descriptions and encounter logic

---

## 🛠️ How to Run

1. Clone the repository:
git clone https://github.com/yourusername/legends-of-valor.git

2. Compile the project:
g++ *.cpp -o LegendsOfValor

3. Run the game:
./LegendsOfValor

---

## 🔮 Future Plans

- 🎨 Add **SFML** for a graphical interface
- 🧠 Introduce multiple skill trees and status effects
- 💀 Add final boss battles and cutscenes
- 🛒 Implement trading, shops, and NPC dialogue

---

## 👨‍💻 Author

Made with C++ by Masroor Ahmad && M.Abdullah  
Semester Project – FAST NUCES

---
