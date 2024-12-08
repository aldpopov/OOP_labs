#ifndef NPC_LOADER_H
#define NPC_LOADER_H

#include "NPC.h"
#include <vector>
#include <memory>

class NPCLoader {
public:
    static std::vector<std::unique_ptr<NPC>> loadNPCs(const std::string& filename);
};

#endif // NPC_LOADER_H