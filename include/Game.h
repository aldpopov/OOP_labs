#ifndef GAME_H
#define GAME_H

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <queue>
#include <tuple>

class Game {
public:
    Game(int mapSize, int numNPCs);
    ~Game();

    void start();
    void stop();
    bool isRunning();
    std::shared_ptr<std::vector<std::unique_ptr<NPC>>> getNPCs();

private:
    void moveNPCs();
    //void battleNPCs();
    void printMap();
    void logKill(NPC* killer, NPC* victim);
    void addBattleTask(NPC* npc1, NPC* npc2, int turn);
    void processBattles();

    std::shared_ptr<std::vector<std::unique_ptr<NPC>>> npcs;
    std::vector<std::thread> threads;
    std::shared_mutex npcsMutex;
    std::mutex cvMutex;
    std::condition_variable cv;
    bool running;
    int mapSize;
    std::mt19937 rng;
    std::unique_ptr<Observer> fileObserver;
    std::queue<std::tuple<NPC*, NPC*, int>> battleQueue;
    std::mutex battleQueueMutex;
    std::condition_variable battleCv;
};

#endif // GAME_H