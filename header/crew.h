#ifndef CREW_H
#define CREW_H

#include <string>

class Crew {
private:
    int _id;
    int _lvl;
    std::string _type;

public:
    Crew(int id, int lvl, std::string type);
    virtual ~Crew() = default;
    virtual int getPrice() const = 0;
    virtual int getRate() const = 0;
    int getId() const;
    int getLvl() const;
    std::string getType() const;
    void setLvl(int lvl);
    void upgrade();
    int getUpgradeCost() const;
};

#endif
