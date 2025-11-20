#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
protected:
    std::string name;
    int maxHP;
    int hp;
    int attackPower;

public:
    Character(const std::string& name, int maxHP, int attackPower);
    virtual ~Character() = default;

    // Actions
    virtual int attack(Character &target); // returns damage dealt
    virtual void takeDamage(int dmg);
    bool isAlive() const;

    // Getters / encapsulation
    std::string getName() const;
    int getHP() const;
    int getMaxHP() const;
    int getAttackPower() const;

    // For healing/support
    virtual void heal(int amount);
};

#endif // CHARACTER_H
