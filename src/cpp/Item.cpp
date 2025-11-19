#include "Item.h"

Item::Item(const std::string& name, int effectValue, Item::Type type)
    : name(name), effectValue(effectValue), type(type) {}

std::string Item::getName() const { return name; }
int Item::getEffectValue() const { return effectValue; }
Item::Type Item::getType() const { return type; }
