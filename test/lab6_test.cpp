#include "gtest/gtest.h"
#include <memory>
#include "NPC.h"
#include "NPC_Loader.h"
#include "Battle_Visitor.h"
#include "NPC_Factory.h"
#include "Observer.h"

TEST(NPCTest, Creation) {
    Dragon dragon("Draco", 100, 100);
    Bull bull("Bully", 150, 150);
    Frog frog("Froggy", 120, 120);

    EXPECT_EQ(dragon.getName(), "Draco");
    EXPECT_EQ(dragon.getX(), 100);
    EXPECT_EQ(dragon.getY(), 100);
    EXPECT_EQ(dragon.getType(), "Dragon");

    EXPECT_EQ(bull.getName(), "Bully");
    EXPECT_EQ(bull.getX(), 150);
    EXPECT_EQ(bull.getY(), 150);
    EXPECT_EQ(bull.getType(), "Bull");

    EXPECT_EQ(frog.getName(), "Froggy");
    EXPECT_EQ(frog.getX(), 120);
    EXPECT_EQ(frog.getY(), 120);
    EXPECT_EQ(frog.getType(), "Frog");
}

TEST(NPCTest, Fight) {
    Dragon dragon("Draco", 100, 100);
    Bull bull("Bully", 150, 150);
    Frog frog("Froggy", 120, 120);

    EXPECT_TRUE(dragon.fight(&bull));
    EXPECT_TRUE(dragon.fight(&frog));

    EXPECT_TRUE(bull.fight(&frog));
    EXPECT_FALSE(bull.fight(&dragon));

    EXPECT_FALSE(frog.fight(&dragon));
    EXPECT_FALSE(frog.fight(&bull));
}

TEST(NPCFactoryTest, CreateNPC) {
    auto dragon = NPCFactory::createNPC("Dragon", "Draco", 100, 100);
    auto bull = NPCFactory::createNPC("Bull", "Bully", 150, 150);
    auto frog = NPCFactory::createNPC("Frog", "Froggy", 120, 120);

    EXPECT_NE(dragon, nullptr);
    EXPECT_EQ(dragon->getType(), "Dragon");
    EXPECT_EQ(dragon->getName(), "Draco");
    EXPECT_EQ(dragon->getX(), 100);
    EXPECT_EQ(dragon->getY(), 100);

    EXPECT_NE(bull, nullptr);
    EXPECT_EQ(bull->getType(), "Bull");
    EXPECT_EQ(bull->getName(), "Bully");
    EXPECT_EQ(bull->getX(), 150);
    EXPECT_EQ(bull->getY(), 150);

    EXPECT_NE(frog, nullptr);
    EXPECT_EQ(frog->getType(), "Frog");
    EXPECT_EQ(frog->getName(), "Froggy");
    EXPECT_EQ(frog->getX(), 120);
    EXPECT_EQ(frog->getY(), 120);
}

TEST(NPCLoaderTest, LoadNPCs) {
    std::string filename = "test_npcs.txt";
    std::ofstream file(filename);
    file << "Dragon Draco 100 100\n";
    file << "Bull Bully 150 150\n";
    file << "Frog Froggy 120 120\n";
    file.close();

    auto npcs = NPCLoader::loadNPCs(filename);

    EXPECT_EQ(npcs.size(), 3);

    EXPECT_NE(npcs[0], nullptr);
    EXPECT_EQ(npcs[0]->getType(), "Dragon");
    EXPECT_EQ(npcs[0]->getName(), "Draco");
    EXPECT_EQ(npcs[0]->getX(), 100);
    EXPECT_EQ(npcs[0]->getY(), 100);

    EXPECT_NE(npcs[1], nullptr);
    EXPECT_EQ(npcs[1]->getType(), "Bull");
    EXPECT_EQ(npcs[1]->getName(), "Bully");
    EXPECT_EQ(npcs[1]->getX(), 150);
    EXPECT_EQ(npcs[1]->getY(), 150);

    EXPECT_NE(npcs[2], nullptr);
    EXPECT_EQ(npcs[2]->getType(), "Frog");
    EXPECT_EQ(npcs[2]->getName(), "Froggy");
    EXPECT_EQ(npcs[2]->getX(), 120);
    EXPECT_EQ(npcs[2]->getY(), 120);
}

class MockObserver : public Observer {
public:
    void update(const std::string& message) override {
        messages.push_back(message);
    }

    std::vector<std::string> messages;
};

TEST(BattleVisitorTest, Battle) {
    auto npcs = std::make_shared<std::vector<std::unique_ptr<NPC>>>();
    npcs->push_back(NPCFactory::createNPC("Dragon", "Draco", 100, 100));
    npcs->push_back(NPCFactory::createNPC("Bull", "Bully", 150, 150));
    npcs->push_back(NPCFactory::createNPC("Frog", "Froggy", 120, 120));

    BattleVisitor battleVisitor(100);
    MockObserver mockObserver;
    battleVisitor.addObserver(&mockObserver);
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

    EXPECT_EQ(npcs->size(), 1); // Все NPC должны быть удалены

    EXPECT_EQ(mockObserver.messages.size(), 2);
    EXPECT_EQ(mockObserver.messages[0], "Draco defeated Bully");
    EXPECT_EQ(mockObserver.messages[1], "Draco defeated Froggy");
}