#include "Player.h"

Player::Player(const std::string& name)
    : Character(name, 100, 18), inventory() {
    // dimulai dengan 3 potion
    inventory.addPotion(3);
}

int Player::attack(Character &target) {
    // simple critical hit chance or other mechanics can be added
    return Character::attack(target);
}

bool Player::usePotion() {
    if (inventory.usePotion()) {
        heal(30); // nge heal 30 HP
        return true;
    }
    return false;
}