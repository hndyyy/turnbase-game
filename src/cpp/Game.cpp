#include "Game.h"
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

Game::Game(const string& playerName)
    : player(playerName), round(1) {
    enemies.emplace_back("Goblin", 40, 10, 5);
    enemies.emplace_back("Orc", 60, 12, 10);
    enemies.emplace_back("Wolf", 35, 9, 3);
}

void Game::showStatus() const {
    cout << "\n\n---- Round " << round << " ----\n";
    cout << player.getName() << " HP: " << player.getHP() << "/" << player.getMaxHP()
              << " | Potions: " << player.getInventory().getPotionCount() << "\n";
    cout << "Enemies:\n";
    for (size_t i = 0; i < enemies.size(); ++i) {
        cout << "  [" << i << "] " << enemies[i].getName()
                  << " HP: " << enemies[i].getHP() << "/" << enemies[i].getMaxHP()
                  << (enemies[i].isAlive() ? "" : " (dead)") << "\n";
    }
    cout << "-------------------\n";
}

void Game::playerTurn() {
    while (true) {
        showStatus();
        cout << "Actions: 1) [Attack]  2) [Use Potion]  3) [Skip]\nChoose: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            cout << "Choose enemy index to attack: ";
            int idx;
            if (!(cin >> idx)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (idx < 0 || idx >= (int)enemies.size() || !enemies[idx].isAlive()) {
                cout << "Invalid target.\n";
                continue;
            }
            int dmg = player.attack(enemies[idx]);
            cout << "You attacked " << enemies[idx].getName() << " for " << dmg << " damage.\n";
            break;
        } else if (choice == 2) {
            if (player.usePotion()) {
                cout << "You used a potion and recovered HP.\n";
            } else {
                cout << "No potions available!\n";
            }
            break;
        } else if (choice == 3) {
            cout << "You skipped your turn.\n";
            break;
        } else {
            cout << "Invalid action. Try again.\n";
        }
    }
}

void Game::enemyTurn() {
    for (auto &e : enemies) {
        if (!e.isAlive()) continue;
        if (!player.isAlive()) break;
        e.aiAction(player);
        cout << e.getName() << " attacked " << player.getName() << " for "
                  << e.getAttackPower() << " damage.\n";
    }
}

bool Game::checkVictory() const {
    for (const auto &e : enemies) {
        if (e.isAlive()) return false;
    }
    return true;
}

bool Game::checkDefeat() const {
    return !player.isAlive();
}

void Game::start() {
    cout << "Welcome, " << player.getName() << "! The battle begins.\n";
    while (true) {
        playerTurn();
        if (checkVictory()) {
            cout << "You defeated all enemies! Victory!\n";
            break;
        }
        enemyTurn();
        if (checkDefeat()) {
            cout << "You have been defeated\n";
            cout << "===GAME OVER===";
            break;
        }
        round++;
    }
}
