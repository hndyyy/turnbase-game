#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Item.h"

class Inventory {
private:
    int potions;
    std::vector<Item> items;

public:
    Inventory();                 // constructor
    void addPotion(int n);       // menambah potion
    bool usePotion();            // memakai potion
    int getPotionCount() const;  // jumlah potion

    // Item management
    void addItem(const Item& item);
    // take item of specific type (pop and return via out param)
    bool takeDamageItem(Item &out);
    bool takeDefenseItem(Item &out);
    int getItemCount() const;
};

#endif
