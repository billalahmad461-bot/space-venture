#include "../header/threat.h"

Threat::Threat(int hp, int dmg, int lvl, sf::Vector2f pos, sf::Vector2f vel)
    : _hp(hp), _dmg(dmg), _lvl(lvl), _position(pos), _velocity(vel) {}

int Threat::getHp() const { return _hp; }

int Threat::getDmg() const { return _dmg; }

int Threat::getLvl() const { return _lvl; }

sf::Vector2f Threat::getPosition() const { return _position; }

void Threat::update() {
    _position += _velocity;
    _sprite.setPosition(_position);
}

void Threat::takeDamage(int dmg) {
    _hp -= dmg;
    if (_hp < 0) _hp = 0;
}

const sf::Sprite& Threat::getSprite() const { return _sprite; }
