#include "../header/bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel, int dmg, bool is_player)
    : _position(pos), _velocity(vel), _dmg(dmg), _is_player(is_player) {
    // Assume rectangle for bullet
    _sprite.setPosition(_position);
}

void Bullet::update() {
    _position += _velocity;
    _sprite.setPosition(_position);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(_sprite);
}

sf::Vector2f Bullet::getPosition() const { return _position; }

int Bullet::getDmg() const { return _dmg; }

bool Bullet::isPlayer() const { return _is_player; }

const sf::Sprite& Bullet::getSprite() const { return _sprite; }
