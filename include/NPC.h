#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>

class NPC {
public:
    NPC(const std::string& name, int x, int y, int moveDistance, int attackDistance);
    virtual ~NPC() = default;

    std::string getName() const;
    int getX() const;
    int getY() const;
    int getMoveDistance() const;
    int getAttackDistance() const;
    bool isAlive() const;
    void setAlive(bool alive);
    void getMapSize(int mapSize);

    virtual std::string getType() const = 0;

    void move();

protected:
    std::string name;
    int x, y;
    int moveDistance;
    int attackDistance;
    bool alive;
    mutable std::mutex mtx;
    int mapSize;
};

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y);

    std::string getType() const override;
};

class Bull : public NPC {
public:
    Bull(const std::string& name, int x, int y);

    std::string getType() const override;

};

class Frog : public NPC {
public:
    Frog(const std::string& name, int x, int y);

    std::string getType() const override;

};

#endif // NPC_H