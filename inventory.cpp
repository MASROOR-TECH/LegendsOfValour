#include "inventory.h"

// Constructor
Inventory::Inventory() : inventorySize(10) { 
    item.reserve(inventorySize); // Reserve space for efficiency
}

// Add item to inventory
bool Inventory::addItem(Item* newItem) {
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
void Item::setName(string n) { name = n; }
void Item::setValue(int v) { value = v; }
void Item::setSize(int s) { size = s; }

string Item::getName() const { return name; }
int Item::getValue() const { return value; }
int Item::getSize() const { return size; }

//=================================================================
void Weapon::useItem() override {}
