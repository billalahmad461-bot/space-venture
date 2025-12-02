#include "../header/weapon.h"

Weapon::Weapon(int lvl, int dmg) : _lvl(lvl), _dmg(dmg) {}

int Weapon::getLvl() const { return _lvl; }

int Weapon::getDmg() const { return _dmg; }

void Weapon::upgrade() {
    _lvl++;
    _dmg += 10;
}
