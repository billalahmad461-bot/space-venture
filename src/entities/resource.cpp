#include "../../header/entities/resource.h"
Resource::Resource(std::string type, int req_equip_lvl, int price, int amount)
    : _type(type), _req_equip_lvl(req_equip_lvl), _price(price), _amount(amount) {}
std::string Resource::getType() const { return _type; }
int Resource::getReqEquipLvl() const { return _req_equip_lvl; }
int Resource::getPrice() const { return _price; }
int Resource::getAmount() const { return _amount; }
void Resource::setAmount(int amount) { _amount = amount; }
void Resource::addAmount(int add) { _amount += add; }
