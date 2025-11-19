#include "Character.h"
#include <algorithm>

Character::Character(const std::string& name, int maxHP, int attackPower, int defense)
    : name(name), maxHP(maxHP), hp(maxHP), attackPower(attackPower), defense(defense) {}

int Character::attack(Character &target) {
    int dmg = attackPower;
    int before = target.getHP();
    target.takeDamage(dmg);
    int after = target.getHP();
    return (before - after);
}

void Character::takeDamage(int dmg) {
    int reduced = dmg - defense;
    if (reduced < 0) reduced = 0;
    hp -= reduced;
    if (hp < 0) hp = 0;
}

bool Character::isAlive() const {
    return hp > 0;
}

std::string Character::getName() const { return name; }
int Character::getHP() const { return hp; }
int Character::getMaxHP() const { return maxHP; }
int Character::getAttackPower() const { return attackPower; }
int Character::getDefense() const { return defense; }

void Character::heal(int amount) {
    hp = std::min(maxHP, hp + amount);
}
