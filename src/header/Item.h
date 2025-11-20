#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string name;
    int effectValue;

public:
    Item(const std::string& name, int effectValue);
    std::string getName() const;
    int getEffectValue() const;
};

#endif // ITEM_H
