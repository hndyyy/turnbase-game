#include "Player.h"
#include "Item.h"

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

bool Player::useDamageItem() {
    Item it("",0,Item::Type::Damage);
    if (inventory.takeDamageItem(it)) {
        // increase attack power
        attackPower += it.getEffectValue();
        return true;
    }
    return false;
}

bool Player::useDefenseItem() {
    Item it("",0,Item::Type::Defense);
    if (inventory.takeDefenseItem(it)) {
        defense += it.getEffectValue();
        return true;
    }
    return false;
}