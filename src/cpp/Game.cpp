#include "Game.h"
#include <iostream>
#include <limits>
#include <vector>
#include <random>
using namespace std;

Game::Game(const string& playerName)
    : player(playerName), round(1), level(1) {
    spawnEnemiesForLevel(level);
}

void Game::spawnEnemiesForLevel(int level) {
    enemies.clear();

    struct EDef { const char* name; int baseHP; int baseAtk; int baseLoot; } defs[] = {
        {"Goblin", 30, 8, 3},
        {"Orc", 45, 11, 6},
        {"Wolf", 28, 7, 2}
    };

    int count = 3 + (level - 1); // increase enemies per level
    for (int i = 0; i < count; ++i) {
        auto &d = defs[i % 3];
        int hp = d.baseHP + (level - 1) * 10;
        int atk = d.baseAtk + (level - 1) * 2;
        int loot = d.baseLoot + (level - 1);
        enemies.emplace_back(d.name, hp, atk, loot);
    }
    cout << "-- Spawning level " << level << " enemies (" << enemies.size() << ") --\n";
}

void Game::showStatus() const {
    cout << "\n\n---- Level " << level << "  Round " << round << " ----\n";
    cout << player.getName() << " HP: " << player.getHP() << "/" << player.getMaxHP()
              << " | DEF: " << player.getDefense()
              << " | Potions: " << player.getInventory().getPotionCount()
              << " | Items: " << player.getInventory().getItemCount() << "\n";
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
        cout << "Actions: 1) [Attack]  2) [Use Potion]  3) [Skip]  4) [Use Item]\nChoose: ";
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
            // If enemy died from this attack, generate loot
            if (!enemies[idx].isAlive()) {
                // RNG setup
                static std::random_device rd;
                static std::mt19937 gen(rd());
                std::uniform_int_distribution<> chance(1, 100);
                int roll = chance(gen);

                if (roll <= 50) {
                    // 50% chance potion
                    player.getInventory().addPotion(1);
                    cout << enemies[idx].getName() << " dropped a potion! You picked it up.\n";
                } else if (roll <= 80) {
                    // 30% chance damage item
                    std::uniform_int_distribution<> dmgVal(2, 6);
                    int val = dmgVal(gen);
                    Item it("Damage Rune", val, Item::Type::Damage);
                    player.getInventory().addItem(it);
                    cout << enemies[idx].getName() << " dropped a Damage Rune (+" << val << " ATK).\n";
                } else {
                    // 20% chance defense item
                    std::uniform_int_distribution<> defVal(1, 4);
                    int val = defVal(gen);
                    Item it("Defense Amulet", val, Item::Type::Defense);
                    player.getInventory().addItem(it);
                    cout << enemies[idx].getName() << " dropped a Defense Amulet (+" << val << " DEF).\n";
                }
            }
            break;
        } else if (choice == 2) {
            if (player.usePotion()) {
                cout << "You used a potion and recovered HP.\n";
            } else {
                cout << "No potions available!\n";
            }
            break;
        } else if (choice == 4) {
            cout << "Item Actions: 1) Use Damage Item  2) Use Defense Item\nChoose: ";
            int ic;
            if (!(cin >> ic)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\n";
                continue;
            }
            if (ic == 1) {
                if (player.useDamageItem()) {
                    cout << "You used a Damage item. Attack increased.\n";
                } else {
                    cout << "No Damage items available.\n";
                }
            } else if (ic == 2) {
                if (player.useDefenseItem()) {
                    cout << "You used a Defense item. Defense increased.\n";
                } else {
                    cout << "No Defense items available.\n";
                }
            } else {
                cout << "Invalid item action.\n";
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
        int dealt = e.attack(player);
        cout << e.getName() << " attacked " << player.getName() << " for "
                  << dealt << " damage.\n";
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
            cout << "You defeated all enemies in this level!\n";
            level++;
            round = 1;
            player.heal(20);
            cout << "Level up! Now level " << level << ". You feel a bit stronger.\n";
            spawnEnemiesForLevel(level);
            continue;
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
