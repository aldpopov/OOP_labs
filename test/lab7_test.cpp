#include "gtest/gtest.h"
#include "NPC.h"
#include "Game.h"
#include <thread>
#include <chrono>

TEST(NPCTest, MoveWithinBounds) {
    Dragon dragon("TestDragon", 5, 5);
    int initialX = dragon.getX();
    int initialY = dragon.getY();
    dragon.getMapSize(10);

    dragon.move();

    int newX = dragon.getX();
    int newY = dragon.getY();

    std::cout << "Initial position: (" << initialX << ", " << initialY << ")" << std::endl;
    std::cout << "New position: (" << newX << ", " << newY << ")" << std::endl;

    EXPECT_GE(newX, 0);
    EXPECT_LT(newX, 10);
    EXPECT_GE(newY, 0);
    EXPECT_LT(newY, 10);
}
TEST(NPCTest, IsAliveInitially) {
    Dragon dragon("TestDragon", 5, 5);
    EXPECT_TRUE(dragon.isAlive());
}

TEST(NPCTest, SetAlive) {
    Dragon dragon("TestDragon", 5, 5);
    dragon.setAlive(false);
    EXPECT_FALSE(dragon.isAlive());
}

TEST(GameTest, StartAndStop) {
    Game game(10, 2);
    game.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    game.stop();
    EXPECT_FALSE(game.isRunning());
}

TEST(GameTest, BattleNPCs) {
    Game game(2, 2);
    auto npcs = game.getNPCs();
    int initialSize = npcs->size();

    game.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    game.stop();

    EXPECT_LT(npcs->size(), initialSize);
}