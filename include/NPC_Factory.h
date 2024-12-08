#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include "NPC.h"
#include <memory>

class NPCFactory {
public:
    static std::unique_ptr<NPC> createNPC(const std::string& type, const std::string& name, int x, int y);
};

#endif // NPC_FACTORY_H