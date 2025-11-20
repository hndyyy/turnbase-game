#include "Game.h"
#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    if (name.empty()) name = "Hero";

    Game game(name);
    game.start();

    return 0;
}
