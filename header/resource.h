#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
private:
    std::string _type;
    int _req_equip_lvl;
    int _price;
    int _amount;

public:
    Resource(std::string type, int req_equip_lvl, int price, int amount = 0);
    std::string getType() const;
    int getReqEquipLvl() const;
    int getPrice() const;
    int getAmount() const;
    void setAmount(int amount);
    void addAmount(int add);
};

#endif
