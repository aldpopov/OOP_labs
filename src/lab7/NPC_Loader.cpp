#include "NPC_Loader.h"
#include "NPC_Factory.h"
#include <fstream>
#include <sstream>

std::vector<std::unique_ptr<NPC>> NPCLoader::loadNPCs(const std::string& filename) {
    std::vector<std::unique_ptr<NPC>> npcs;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type, name;
        int x, y;
        iss >> type >> name >> x >> y;
        npcs.push_back(NPCFactory::createNPC(type, name, x, y));
    }

    return npcs;
}