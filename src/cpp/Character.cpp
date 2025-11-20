#include "Character.h"
#include <algorithm>

Character::Character(const std::string& name, int maxHP, int attackPower)
    : name(name), maxHP(maxHP), hp(maxHP), attackPower(attackPower) {}

int Character::attack(Character &target) {
    int dmg = attackPower;
    target.takeDamage(dmg);
    return dmg;
}

void Character::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}

bool Character::isAlive() const {
    return hp > 0;
}

std::string Character::getName() const { return name; }
int Character::getHP() const { return hp; }
int Character::getMaxHP() const { return maxHP; }
int Character::getAttackPower() const { return attackPower; }

void Character::heal(int amount) {
    hp = std::min(maxHP, hp + amount);
}
