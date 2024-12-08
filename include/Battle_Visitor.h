#ifndef BATTLE_VISITOR_H
#define BATTLE_VISITOR_H

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>

class BattleVisitor {
public:
    BattleVisitor(int range);

    void visit(NPC* npc);

    void setNPCs(std::shared_ptr<std::vector<std::unique_ptr<NPC>>> npcs);

    void addObserver(Observer* observer);

private:
    bool canFight(NPC* npc1, NPC* npc2);

    void notifyObservers(const std::string& message);

    int range;
    std::shared_ptr<std::vector<std::unique_ptr<NPC>>> npcs;
    std::vector<Observer*> observers;
};

#endif // BATTLE_VISITOR_H