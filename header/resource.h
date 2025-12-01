#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
private:
    std::string _type;
    bool _lock;
    int _price;
    int _amount;  // Added missing attribute for quantity

public:
    Resource(std::string type, bool lock, int price, int amount = 1);
    std::string getType() const;
    bool isLocked() const;
    int getPrice() const;
    int getAmount() const;
    void setAmount(int amount);
    void addAmount(int add);
};

#endif
