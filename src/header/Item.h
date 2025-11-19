#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    enum class Type {
        Damage,
        Defense,
        Potion
    };

private:
    std::string name;
    int effectValue;
    Type type;

public:
    Item(const std::string& name, int effectValue, Type type);
    std::string getName() const;
    int getEffectValue() const;
    Type getType() const;
};

#endif // ITEM_H
