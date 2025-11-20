#include "Inventory.h"

Inventory::Inventory() : potions(0) {}

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
