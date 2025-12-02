#include "../header/equipment.h"

Equipment::Equipment(int lvl, int max_capacity) : _lvl(lvl), _max_capacity(max_capacity) {}

void Equipment::upgrade() {
    _lvl++;
    // Optionally increase max_capacity
}

int Equipment::getLvl() const { return _lvl; }
