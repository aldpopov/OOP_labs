#include <iostream>
#include <vector>
#include <memory>
#include "NPC.h"
#include "NPC_Factory.h"
#include "NPC_Loader.h"
#include "Battle_Visitor.h"
#include "Observer.h"

int main() {
    auto npcs = std::make_shared<std::vector<std::unique_ptr<NPC>>>();
    BattleVisitor battleVisitor(100);

    FileObserver fileObserver("log.txt");
    ScreenObserver screenObserver;
    battleVisitor.addObserver(&fileObserver);
    battleVisitor.addObserver(&screenObserver);

    npcs->push_back(NPCFactory::createNPC("Dragon", "Draco", 100, 100));
    npcs->push_back(NPCFactory::createNPC("Bull", "Bully", 150, 150));
    npcs->push_back(NPCFactory::createNPC("Frog", "Froggy", 120, 120));

    auto loadedNPCs = NPCLoader::loadNPCs("npcs.txt");
    npcs->insert(npcs->end(), std::make_move_iterator(loadedNPCs.begin()), std::make_move_iterator(loadedNPCs.end()));

    for (const auto& npc : *npcs) {
        if (npc) {
            std::cout << npc->getType() << " " << npc->getName() << " at (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
        }
    }

    battleVisitor.setNPCs(npcs);
    for (auto it = npcs->begin(); it != npcs->end(); ++it) {
        if (*it) {
            (*it)->accept(&battleVisitor);
        }
    }

    npcs->erase(std::remove_if(npcs->begin(), npcs->end(), [](const std::unique_ptr<NPC>& npc) {
        return npc == nullptr;
    }), npcs->end());

    std::cout << "Survivors:" << std::endl;
    for (const auto& npc : *npcs) {
        if (npc) {
            std::cout << npc->getType() << " " << npc->getName() << " at (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
        }
    }

    return 0;
}