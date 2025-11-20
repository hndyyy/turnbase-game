#include "Item.h"

Item::Item(const std::string& name, int effectValue)
    : name(name), effectValue(effectValue) {}

std::string Item::getName() const { return name; }
int Item::getEffectValue() const { return effectValue; }
