#include "../../header/entities/weapon.h"
Weapon::Weapon(int lvl, int dmg) : _lvl(lvl), _dmg(dmg), _fire_rate(2.0f) {}
int Weapon::getLvl() const { return _lvl; }
int Weapon::getDmg() const { return _dmg; }
float Weapon::getFireRate() const { return _fire_rate; }
void Weapon::upgrade() {
    _lvl++;
    _dmg += 10;
    _fire_rate += 0.5f;
}
