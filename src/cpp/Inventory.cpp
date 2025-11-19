#include "Inventory.h"
#include <algorithm>

Inventory::Inventory() : potions(0), items() {}

void Inventory::addPotion(int n) {
    if (n > 0) potions += n;
}

bool Inventory::usePotion() {
    if (potions > 0) {
        potions--;
        return true;
    }
    return false;
}

int Inventory::getPotionCount() const {
    return potions;
}

void Inventory::addItem(const Item &item) {
    items.push_back(item);
}

bool Inventory::takeDamageItem(Item &out) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getType() == Item::Type::Damage) {
            out = *it;
            items.erase(it);
            return true;
        }
    }
    return false;
}

bool Inventory::takeDefenseItem(Item &out) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getType() == Item::Type::Defense) {
            out = *it;
            items.erase(it);
            return true;
        }
    }
    return false;
}

int Inventory::getItemCount() const {
    return static_cast<int>(items.size());
}
