#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Inventory.h"

class Player : public Character {
private:
    Inventory inventory;

public:
    Player(const std::string& name);

    int attack(Character &target) override;
    bool usePotion();

    // Use items from inventory
    bool useDamageItem();
    bool useDefenseItem();

    // Getter untuk inventory
    Inventory& getInventory() { 
        return inventory;
    }

    // Getter versi const (agar bisa dipanggil dari fungsi const Game::showStatus)
    const Inventory& getInventory() const {
        return inventory;
    }
};

#endif
