#include "../header/shield.h"
#include <algorithm> // For std::min

Shield::Shield(int lvl, int hp) : _lvl(lvl), _hp(hp), _current_hp(hp) {}

int Shield::getLvl() const { return _lvl; }

int Shield::getHp() const { return _hp; }

int Shield::getCurrentHp() const { return _current_hp; }

void Shield::setCurrentHp(int hp) { _current_hp = hp; }

void Shield::upgrade() {
    _lvl++;
    _hp += 50;
    _current_hp = _hp;
}

void Shield::takeDamage(int dmg) {
    _current_hp -= dmg;
    if (_current_hp < 0) _current_hp = 0;
}

void Shield::regen(int amt) {
    _current_hp = std::min(_current_hp + amt, _hp);
}
