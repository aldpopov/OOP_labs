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
    BattleVisitor battleVisitor(100); // Дальность сражения 100 метров

    // Добавляем наблюдателей
    FileObserver fileObserver("log.txt");
    ScreenObserver screenObserver;
    battleVisitor.addObserver(&fileObserver);
    battleVisitor.addObserver(&screenObserver);

    // Добавляем NPC
    npcs->push_back(NPCFactory::createNPC("Dragon", "Draco", 100, 100));
    npcs->push_back(NPCFactory::createNPC("Bull", "Bully", 150, 150));
    npcs->push_back(NPCFactory::createNPC("Frog", "Froggy", 120, 120));

    // Загружаем NPC из файла
    auto loadedNPCs = NPCLoader::loadNPCs("npcs.txt");
    npcs->insert(npcs->end(), std::make_move_iterator(loadedNPCs.begin()), std::make_move_iterator(loadedNPCs.end()));

    // Печатаем список NPC
    for (const auto& npc : *npcs) {
        if (npc) {
            std::cout << npc->getType() << " " << npc->getName() << " at (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
        }
    }

    // Запускаем боевой режим
    battleVisitor.setNPCs(npcs);
    for (auto it = npcs->begin(); it != npcs->end(); ++it) {
        if (*it) {
            (*it)->accept(&battleVisitor);
        }
    }

    // Очищаем вектор от удаленных объектов
    npcs->erase(std::remove_if(npcs->begin(), npcs->end(), [](const std::unique_ptr<NPC>& npc) {
        return npc == nullptr;
    }), npcs->end());

    // Печатаем оставшихся NPC
    std::cout << "Survivors:" << std::endl;
    for (const auto& npc : *npcs) {
        if (npc) {
            std::cout << npc->getType() << " " << npc->getName() << " at (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
        }
    }

    return 0;
}