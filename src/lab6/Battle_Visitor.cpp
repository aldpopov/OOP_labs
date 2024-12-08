#include "Battle_Visitor.h"
#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

BattleVisitor::BattleVisitor(int range) : range(range), npcs(nullptr) {}

void BattleVisitor::visit(NPC* npc) {
    if (!npcs) return;

    for (auto it = npcs->begin(); it != npcs->end(); ++it) {
        if (*it && npc != it->get() && canFight(npc, it->get())) {
            if (npc->fight(it->get()) && !it->get()->fight(npc)) {
                notifyObservers(npc->getName() + " defeated " + it->get()->getName());
                it->reset();
            } else if (it->get()->fight(npc) && !npc->fight(it->get())) {
                notifyObservers(it->get()->getName() + " defeated " + npc->getName());
                npc->accept(this); // Удаляем npc
                return;
            } else if (it->get()->fight(npc) && npc->fight(it->get())){
                notifyObservers("Both " + npc->getName() + " and " + it->get()->getName() + " died in battle");
                it->reset();
                npc->accept(this); // Удаляем npc
                return;
            }
        }
    }
}

void BattleVisitor::setNPCs(std::shared_ptr<std::vector<std::unique_ptr<NPC>>> npcs) {
    this->npcs = npcs;
}

void BattleVisitor::addObserver(Observer* observer) {
    observers.push_back(observer);
}

bool BattleVisitor::canFight(NPC* npc1, NPC* npc2) {
    return std::pow(std::pow(npc2->getX() - npc1->getX(), 2) + std::pow(npc2->getY() - npc1->getY(), 2), 0.5) <= range;
    /*return std::abs(npc1->getX() - npc2->getX()) <= range &&
           std::abs(npc1->getY() - npc2->getY()) <= range;*/
}

void BattleVisitor::notifyObservers(const std::string& message) {
    for (auto& observer : observers) {
        observer->update(message);
    }
}