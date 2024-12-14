#include "Game.h"
#include <chrono>
#include <thread>

int main() {
    Game game(15, 5);
    game.start();

    std::this_thread::sleep_for(std::chrono::seconds(10));

    game.stop();

    std::cout << "Survivors:" << std::endl;
    auto npcs = game.getNPCs();
    for (const auto& npc : *npcs) {
        if (npc && npc->isAlive()) {
            std::cout << npc->getType() << " " << npc->getName() << " at (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
        }
        if (npcs->size() == 0) {
            std::cout << "Not a single one, it seems... War never changes..." << std::endl;
        }
    }

    return 0;
}