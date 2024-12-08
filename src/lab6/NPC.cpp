#include "NPC.h"
#include "Battle_Visitor.h"

NPC::NPC(const std::string& name, int x, int y) : name(name), x(x), y(y) {}

std::string NPC::getName() const { return name; }
int NPC::getX() const { return x; }
int NPC::getY() const { return y; }

void NPC::accept(BattleVisitor* visitor) {
    visitor->visit(this);
}

Dragon::Dragon(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Dragon::getType() const { return "Dragon"; }

bool Dragon::fight(NPC* other) {
    if (other->getType() == "Bull" || other->getType() == "Dragon" || other->getType() == "Frog") {
        return true; // Дракон побеждает быка
    }
    return false;
}

Bull::Bull(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Bull::getType() const { return "Bull"; }

bool Bull::fight(NPC* other) {
    if (other->getType() == "Frog" || other->getType() == "Bull") {
        return true; // Бык побеждает жабу
    }
    return false;
}

Frog::Frog(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Frog::getType() const { return "Frog"; }

bool Frog::fight(NPC* other) {
    return false; // Жаба всегда проигрывает
}