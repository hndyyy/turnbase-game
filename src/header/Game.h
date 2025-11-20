#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game {
private:
    Player player;
    std::vector<Enemy> enemies;
    int round;

    void showStatus() const;
    void playerTurn();
    void enemyTurn();
    bool checkVictory() const;
    bool checkDefeat() const;

public:
    Game(const std::string& playerName);
    void start(); // main loop
};

#endif // GAME_H
