#include "inventory.h"

// Constructor
Inventory::Inventory() : inventorySize(30) { 
    item.reserve(inventorySize); // Reserve space for efficiency
}

// Add item to inventory
bool Inventory::addItem(Item* newItem) {
    if(newItem==nullptr){
        cout << "Error: Cannot add a null item to the inventory.\n";
        return false;
    }
    if (item.size() >= inventorySize) {
        cout << "Inventory is full! Cannot add " << newItem->getName() << ".\n";
        return false;
    }
    item.push_back(newItem);
    return true;
}

// Get item by name
Item* Inventory::getItem(string name) {
    for (Item* it : item) {
        if (it->getName() == name) {
            return it;
        }
    }
    return nullptr;
}

// Remove item by name
bool Inventory::removeItem(string itemName) {
    for (auto it = item.begin(); it != item.end(); ++it) {
        if ((*it)->getName() == itemName) {
            delete* it;         // Free memory
            item.erase(it);     // Remove from vector
            return true;
        }
    }
    return false;
}

// Display all items
void Inventory::showInventory() const {
    if (item.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    cout << "\n========= Inventory Contents =========\n";
    for (Item* it : item) {
        cout << "- " << it->getName()
            << " | Value: " << it->getValue()
            << " | Size: " << it->getSize() << '\n';
    }
    cout << "======================================\n";
}

// Return max inventory size
int Inventory::getInventorySize() const {
    return inventorySize;
}

// Destructor
Inventory::~Inventory() {
    for (Item* it : item) {
        delete it;
    }
    item.clear();
}


//========================Item Class===============================
void Item::setName(string n) { 
    name = n; 
}
void Item::setValue(int v) { 
    value = v; 
}
void Item::setSize(int s) { 
    size = s; 
}

string Item::getName() const { 
    return name; 
}
int Item::getValue() const { 
    return value; 
}
int Item::getSize() const { 
    return size; 
}

//=================================================================
void Weapon::useItem(Character& player) {
    cout << "You equipped: " << getName() << endl;
    attack = 0;
    if (getName() == "Wooden Sword") {
        cout << "+5 Attack applied.\n"; attack = 5;
    }
    else if (getName() == "Iron Sword") {
        cout << "+10 Attack applied.\n"; attack = 10;
    }
    else if (getName() == "Golden Sword") {
        cout << "+15 Attack applied.\n"; attack = 15;
    }
    else {
        cout << "Standard weapon equipped. No bonus detected.\n";
    }
    player.setAttack(player.getAttack() + attack);
}



//=================================================================
void Armor::useItem(Character& player) {
        cout << "You equipped: " << getName() << endl;
        defense = 0;
        if (getName() == "Wooden Shield") {
            cout << "+5 Defense applied.\n"; defense = 5;
        }
        else if (getName() == "Iron Armor") {
            cout << "+10 Defense applied.\n"; defense = 10;
        }
        else if (getName() == "Golden Plate") {
            cout << "+15 Defense applied.\n"; defense = 15;
        }
        else {
            cout << "Standard armor equipped. No bonus detected.\n";
        }
        player.setDefense(player.getDefense() + defense);
}


//=================================================================

void Potion::useItem(Character& player) {
    if (numOfPotions <= 0) {
        cout << "No potions left.\n";
        return;
    }
    --numOfPotions;

    switch (type) {
        case HEAL:
            player.setHealth(player.getHealth() + potionPower);
            cout << "Health increased by " << potionPower << "\n";
            break;
        case ATTACK:
            player.setAttack(player.getAttack() + potionPower);
            cout << "Attack increased by " << potionPower << ".\n";
            break;
        case DEFENSE:
            player.setDefense(player.getDefense() + potionPower);
            cout << "Defense increased by " << potionPower << ".\n";
            break;
        }
}


//============================================================
Item* Collectable::buyItem() {
    cout << "\nYou used: " << getName() << ".\n";
    cout << "It glows and opens a magical shop...\n";
    cout << "\nChoose one item to receive:\n";
    cout << "1. Healing Potion\n";
    cout << "2. Iron Sword\n";
    cout << "3. Iron Armor\n";
    cout << "Choice: ";

    char choice;
    cin >> choice;
    cin.ignore();
    Item* reward = nullptr;

    switch (choice) {
    case '1': {
        Potion* potion = new Potion();
        potion->setName("Healing Potion");
        potion->setValue(20);
        potion->setSize(1);
       potion->setPotionType(0); // HEAL
        reward = potion;
        break;
    }
    case '2': {
        Weapon* sword = new Weapon();
        sword->setName("Iron Sword");
        sword->setValue(10); // attack power
        sword->setSize(2);
        reward = sword;
        break;
    }
    case '3': {
        Armor* armor = new Armor();
        armor->setName("Iron Armor");
        armor->setValue(10); // defense value
        armor->setSize(2);
        reward = armor;
        break;
    }
    default:
        cout << "Invalid choice. You lost the token.\n";
        return nullptr;
    }
    cout << "You received: " << reward->getName() << "!\n";
    return reward;

}


//======================================================
potionType Potion::getPotionType() const {
    return type; // Return enum as int (0 = HEAL, 1 = ATTACK, 2 = DEFENSE)
}
void Potion::setPotionType(int t) {
    if (t >= 0 && t <= 2) {
        type = static_cast<potionType>(t); // Safely cast int to enum
    }
    else {
        cout << "Invalid potion type. Must be 0 (HEAL), 1 (ATTACK), or 2 (DEFENSE).\n";
    }
}


//=============================================
 // Parameterized constructor
Weapon::Weapon(weaponType t) {
    type = t;
    if (type == 1) {
        setValue(25);
        attack = 20;
        setName("Cursed Sword");
    }
    else if (type == 2) {
        setValue(30);
        attack = 25;
        setName("Lightning Axe");
    }
    else if (type == 3) {
        setValue(20);
        attack = 22;
        setName("Magical Wand");
    }
    else {
        cout << "Invalid Weapon Type" << endl;
    }
    setSize(6);
}

Armor::Armor(armorType t) {
    type = t;
    setSize(5);
    if (type == 1) {
        setValue(20);
        defense = 10;
        setName("Bronze Shield");
    }
    else if (type == 2) {
        setValue(25);
        defense = 15;
        setName("Gold Shield");
    }
    else if (type == 3) {
        setValue(30);
        defense = 20;
        setName("Diamond Shield");
    }
    else {
        cout << "Invalid Armor Type" << endl;
    }
}

Potion::Potion(potionType t) {
    type = t;
    setSize(3);
    numOfPotions = 0;
    if (type == 1) {
        setValue(10);
        power = 40;
        setName("Healing Potion");
    }
    else if (type == 2) {
        setValue(10);
        power = 15;
        setName("Attack Potion");
    }
    else if (type == 3) {
        setValue(25);
        power = 0;
        setName("Revival Potion");
    }
    else {
        cout << "Invalid Armor Type" << endl;
    }
}
