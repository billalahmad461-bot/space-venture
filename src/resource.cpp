#include "../header/resource.h"

Resource::Resource(std::string type, bool lock, int price, int amount)
    : _type(type), _lock(lock), _price(price), _amount(amount) {}

std::string Resource::getType() const { return _type; }

bool Resource::isLocked() const { return _lock; }

int Resource::getPrice() const { return _price; }

int Resource::getAmount() const { return _amount; }

void Resource::setAmount(int amount) { _amount = amount; }

void Resource::addAmount(int add) { _amount += add; }
