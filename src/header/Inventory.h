#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory {
private:
    int potions;

public:
    Inventory();                 // constructor
    void addPotion(int n);       // menambah potion
    bool usePotion();            // memakai potion
    int getPotionCount() const;  // jumlah potion
};

#endif
