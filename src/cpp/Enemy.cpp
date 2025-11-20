#include "Enemy.h"

Enemy::Enemy(const std::string& name, int hp, int atk, int loot)
    : Character(name, hp, atk), loot(loot) {}

int Enemy::attack(Character &target) {
    // could add randomness here
    return Character::attack(target);
}

int Enemy::getLoot() const {
    return loot;
}

void Enemy::aiAction(Character &player) {
    // For now, always attack
    if (isAlive()) {
        attack(player);
    }
}
