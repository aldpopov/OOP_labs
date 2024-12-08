#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include <memory>

class NPC {
public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    std::string getName() const;
    int getX() const;
    int getY() const;

    virtual std::string getType() const = 0;

    virtual bool fight(NPC* other) = 0;

    void accept(class BattleVisitor* visitor);

protected:
    std::string name;
    int x, y;
};

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y);

    std::string getType() const override;

    bool fight(NPC* other) override;
};

class Bull : public NPC {
public:
    Bull(const std::string& name, int x, int y);

    std::string getType() const override;

    bool fight(NPC* other) override;
};

class Frog : public NPC {
public:
    Frog(const std::string& name, int x, int y);

    std::string getType() const override;

    bool fight(NPC* other) override;
};

#endif // NPC_H