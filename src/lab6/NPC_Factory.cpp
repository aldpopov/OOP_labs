#include "NPC_Factory.h"
#include "NPC.h"
#include <memory>

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Dragon") {
        return std::make_unique<Dragon>(name, x, y);
    } else if (type == "Bull") {
        return std::make_unique<Bull>(name, x, y);
    } else if (type == "Frog") {
        return std::make_unique<Frog>(name, x, y);
    }
    return nullptr;
}