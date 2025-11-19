#include <iostream>
#include <string>
using namespace std;

// ======================================
// Base Entity (Character & Enemy)
// ======================================
class Entity {
protected:
    string name;
    int hp, maxHp;
    int attackPower;
    int defense;
    bool debuffActive = false;

public:
    Entity(string n, int hp, int atk, int def)
        : name(n), hp(hp), maxHp(hp), attackPower(atk), defense(def) {}

    string getName() { return name; }
    int getHP() { return hp; }

    bool isDead() { return hp <= 0; }

    void takeDamage(int dmg) {
        int actual = dmg - defense;
        if (actual < 0) actual = 0;
        hp -= actual;
        if (hp < 0) hp = 0;
        cout << name << " menerima " << actual << " damage! (HP: " << hp << ")\n";
    }

    void heal(int amount) {
        hp += amount;
        if (hp > maxHp) hp = maxHp;
        cout << name << " meng-heal " << amount << " (HP: " << hp << ")\n";
    }

    void applyDebuff() {
        debuffActive = true;
        cout << name << " terkena debuff!\n";
    }

    void clearDebuff() {
        debuffActive = false;
        cout << name << " debuff hilang!\n";
    }

    bool hasDebuff() { return debuffActive; }
};

// ======================================
// Character Class
// ======================================
class Character : public Entity {
public:
    Character(string n, int hp, int atk, int def)
        : Entity(n, hp, atk, def) {}

    void buff() {
        attackPower += 5;
        cout << name << " meningkatkan attack! (+5)\n";
    }

    void cleanse() {
        if (debuffActive) {
            debuffActive = false;
            cout << name << " menghapus debuff!\n";
        } else {
            cout << name << " tidak memiliki debuff.\n";
        }
    }

    void attack(Entity &enemy) {
        cout << name << " menyerang " << enemy.getName() << "!\n";
        enemy.takeDamage(attackPower);
    }
};

// ======================================
// Enemy Class
// ======================================
class Enemy : public Entity {
public:
    Enemy(string n, int hp, int atk, int def)
        : Entity(n, hp, atk, def) {}

    void attack(Entity &player) {
        cout << name << " menyerang " << player.getName() << "!\n";
        player.takeDamage(attackPower);
    }
};

// ======================================
// Game Logic
// ======================================
int main() {
    Character player("Hero", 100, 20, 5);
    Enemy goblin("Goblin", 80, 15, 3);

    while (!player.isDead() && !goblin.isDead()) {
        cout << "\n=== Turn Kamu ===\n";
        cout << "1. Attack\n";
        cout << "2. Heal\n";
        cout << "3. Buff\n";
        cout << "4. Cleanse Debuff\n";
        cout << "> Pilih aksi: ";

        int pilih;
        cin >> pilih;

        switch (pilih) {
            case 1: player.attack(goblin); break;
            case 2: player.heal(20); break;
            case 3: player.buff(); break;
            case 4: player.cleanse(); break;
            default: cout << "Pilihan tidak valid.\n"; break;
        }

        if (goblin.isDead()) break;

        cout << "\n=== Turn Musuh ===\n";
        goblin.attack(player);
    }

    cout << "\n===== MATCH END =====\n";
    if (player.isDead()) cout << "Kamu Kalah!\n";
    else cout << "Kamu Menang!\n";
}
