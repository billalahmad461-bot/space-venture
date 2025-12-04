#include "../../header/crew/crew.h"
Crew::Crew(int id, int lvl, std::string type)
    : _id(id), _lvl(lvl), _type(type) {}
int Crew::getId() const { return _id; }
int Crew::getLvl() const { return _lvl; }
std::string Crew::getType() const { return _type; }
void Crew::setLvl(int lvl) { _lvl = lvl; }
void Crew::upgrade() {
    _lvl++;
}
int Crew::getUpgradeCost() const {
    return _lvl * 20;
}
