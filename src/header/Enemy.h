#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
private:
    int loot;

public:
    Enemy(const std::string& name, int hp, int atk, int loot);
    int attack(Character &target) override;
    int getLoot() const;
    void aiAction(Character &player); // simple AI action method
};

#endif // ENEMY_H
