#include "../header/engineer.h"

Engineer::Engineer(int id, int lvl, int price, int work_rate)
    : Crew(id, lvl, "engineer"), _price(price), _work_rate(work_rate) {}

int Engineer::getPrice() const { return _price; }

int Engineer::getRate() const { return _work_rate; }
