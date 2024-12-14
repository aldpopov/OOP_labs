#include "Game.h"
#include "NPC_Factory.h"
#include "Observer.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <bits/algorithmfwd.h>

Game::Game(int mapSize, int numNPCs) : running(false), mapSize(mapSize), rng(std::random_device{}()) {
    npcs = std::make_shared<std::vector<std::unique_ptr<NPC>>>();
    std::uniform_int_distribution<> dis(0, mapSize - 1);
    for (int i = 0; i < numNPCs; ++i) {
        int x = dis(rng);
        int y = dis(rng);
        std::string type = (i % 3 == 0) ? "Dragon" : (i % 3 == 1) ? "Bull" : "Frog";
        auto npc = NPCFactory::createNPC(type, "NPC" + std::to_string(i), x, y);
        npc->getMapSize(mapSize);
        npcs->push_back(std::move(npc));
        
    }
    fileObserver = std::make_unique<FileObserver>("log.txt");
}

Game::~Game() {
    stop();
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Game::start() {
    running = true;
    threads.emplace_back(&Game::moveNPCs, this);
    threads.emplace_back(&Game::processBattles, this);
    threads.emplace_back(&Game::printMap, this);
}

void Game::stop() {
    running = false;
    cv.notify_all();
    battleCv.notify_all();
}

void Game::moveNPCs() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::shared_lock<std::shared_mutex> lock(npcsMutex);
        for (auto& npc : *npcs) {
            if (npc && npc->isAlive()) {
                npc->move();
            }
        }

        for (auto it1 = npcs->begin(); it1 != npcs->end(); ++it1) {
            if (!(*it1) || !(*it1)->isAlive()) continue;
            for (auto it2 = std::next(it1); it2 != npcs->end(); ++it2) {
                if (!(*it2) || !(*it2)->isAlive()) continue;
                int dist = std::round(std::pow(std::pow((*it2)->getX() - (*it1)->getX(), 2) + std::pow((*it2)->getY() - (*it1)->getY(), 2), 0.5));
                if (dist <= (*it1)->getAttackDistance() && (dist) <= (*it2)->getAttackDistance()) {
                    addBattleTask((*it1).get(), (*it2).get(), 0);
                } else if (dist <= (*it1)->getAttackDistance() && dist > (*it2)->getAttackDistance()) {
                    addBattleTask((*it1).get(), (*it2).get(), 1);
                } else if (dist > (*it1)->getAttackDistance() && dist <= (*it2)->getAttackDistance()) {
                    addBattleTask((*it1).get(), (*it2).get(), 2);
                }
            }
        }

        cv.notify_one();
    }
}

void Game::addBattleTask(NPC* npc1, NPC* npc2, int turn) {
    std::lock_guard<std::mutex> lock(battleQueueMutex);
    battleQueue.push(std::make_tuple(npc1, npc2, turn));
    battleCv.notify_one();
}

void Game::processBattles() {
    while (running) {
        std::unique_lock<std::mutex> lock(battleQueueMutex);
        battleCv.wait(lock, [this] { return !running || !battleQueue.empty(); });
        if (!running) break;

        auto battleTask = battleQueue.front();
        battleQueue.pop();
        lock.unlock();

        NPC* npc1 = std::get<0>(battleTask);
        NPC* npc2 = std::get<1>(battleTask);
        int turn = std::get<2>(battleTask);

        if (npc1 && npc2 && npc1->isAlive() && npc2->isAlive()) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 6);
            int attack1 = dis(gen);
            int defense2 = dis(gen);
            int attack2 = dis(gen);
            int defense1 = dis(gen);
            if (turn == 0) {
                if (attack1 >= defense2) {
                    logKill(npc1, npc2);
                    npc2->setAlive(false);
                }
                if (attack2 >= defense1) {
                    logKill(npc2, npc1);
                    npc1->setAlive(false);
                }
            } else if (turn == 1) {
                if (attack1 >= defense2) {
                    logKill(npc1, npc2);
                    npc2->setAlive(false);
                }
            } else if (turn == 2) {
                if (attack2 >= defense1) {
                    logKill(npc2, npc1);
                    npc1->setAlive(false);
                }
            }
            std::unique_lock<std::shared_mutex> npcsLock(npcsMutex);
            npcs->erase(std::remove_if(npcs->begin(), npcs->end(), [](const std::unique_ptr<NPC>& npc) {
                return npc == nullptr || !npc->isAlive();
            }), npcs->end());
        }
    }
}
/*
void Game::battleNPCs() {
    while (running) {
        std::unique_lock<std::mutex> cvLock(cvMutex);
        cv.wait(cvLock, [this] { return !running || !npcs->empty(); });
        if (!running) break;

        std::unique_lock<std::shared_mutex> lock(npcsMutex);
        for (auto it1 = npcs->begin(); it1 != npcs->end(); ++it1) {
            if (!(*it1) || !(*it1)->isAlive()) continue;
            for (auto it2 = std::next(it1); it2 != npcs->end(); ++it2) {
                if (!(*it2) || !(*it2)->isAlive()) continue;
                if (std::pow(std::pow((*it2)->getX() - (*it1)->getX(), 2) + std::pow((*it2)->getY() - (*it1)->getY(), 2), 0.5) <= (*it1)->getAttackDistance()) {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(1, 6);
                    int attack1 = dis(gen);
                    int defense2 = dis(gen);
                    //int attack2 = dis(gen);
                    //int defense1 = dis(gen);

                    if (attack1 >= defense2) {
                        logKill((*it1).get(), (*it2).get());
                        (*it2)->setAlive(false);
                    }
                    if (attack2 >= defense1) {
                        logKill((*it2).get(), (*it1).get());
                        (*it1)->setAlive(false);
                    }
                }
            }
        }

        // Очищаем вектор от удаленных объектов
        npcs->erase(std::remove_if(npcs->begin(), npcs->end(), [](const std::unique_ptr<NPC>& npc) {
            return npc == nullptr || !npc->isAlive();
        }), npcs->end());
    }
}*/
void Game::printMap() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::shared_lock<std::shared_mutex> lock(npcsMutex);
        std::vector<std::vector<char>> map(mapSize, std::vector<char>(mapSize, '.'));
        for (const auto& npc : *npcs) {
            if (npc && npc->isAlive()) {
                int x = npc->getX();
                int y = npc->getY();
                char symbol = npc->getType()[0];
                map[y][x] = symbol;
            }
        }

        std::cout << "Map:" << std::endl;
        for (const auto& row : map) {
            for (char cell : row) {
                std::cout << cell;
            }
            std::cout << std::endl;
        }
    }
}
void Game::logKill(NPC* killer, NPC* victim) {
    std::string message = killer->getName() + "(" + killer->getType() + ") defeated " +
                          victim->getName() + "(" + victim->getType() + ") at (" +
                          std::to_string(killer->getX()) + ", " + std::to_string(killer->getY()) + ") - (" +
                          std::to_string(victim->getX()) + ", " + std::to_string(victim->getY()) + ")";
    fileObserver->update(message);
}

std::shared_ptr<std::vector<std::unique_ptr<NPC>>> Game::getNPCs() {
    return npcs;
}

bool Game::isRunning() {
    return running;
}