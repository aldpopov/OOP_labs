#include "NPC.h"
#include <random>

NPC::NPC(const std::string& name, int x, int y, int moveDistance, int attackDistance)
    : name(name), x(x), y(y), moveDistance(moveDistance), attackDistance(attackDistance), alive(true), mapSize(1) {}

std::string NPC::getName() const { return name; }
int NPC::getX() const { return x; }
int NPC::getY() const { return y; }
int NPC::getMoveDistance() const { return moveDistance; }
int NPC::getAttackDistance() const { return attackDistance; }
bool NPC::isAlive() const { return alive; }
void NPC::setAlive(bool alive) { this->alive = alive; }

void NPC::move() {
    std::lock_guard<std::mutex> lock(mtx);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-moveDistance, moveDistance);
    std::uniform_int_distribution<> axisDis(0, 1);

    int axis = axisDis(gen);
    if (axis == 0) {
        int newX = x + dis(gen);
        if (newX >= 0 && newX < mapSize) {
            x = newX;
        } else if(newX < 0) {
            x = 0;
        } else if(newX >= mapSize) {
            x = mapSize - 1;
        }
    } else {
        int newY = y + dis(gen);
        if (newY >= 0 && newY < mapSize) {
            y = newY;
        } else if(newY < 0) {
            y = 0;
        } else if(newY >= mapSize) {
            y = mapSize - 1;
        }
    }
}

void NPC::getMapSize(int mapSize) {
    this->mapSize = mapSize;
}

Dragon::Dragon(const std::string& name, int x, int y) : NPC(name, x, y, 5, 3) {}

std::string Dragon::getType() const { return "Dragon"; }

Bull::Bull(const std::string& name, int x, int y) : NPC(name, x, y, 3, 4) {}

std::string Bull::getType() const { return "Bull"; }

Frog::Frog(const std::string& name, int x, int y) : NPC(name, x, y, 1, 5) {}

std::string Frog::getType() const { return "Frog"; }
