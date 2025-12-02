#include "../header/bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel, int dmg, bool is_player)
    : _position(pos), _velocity(vel), _dmg(dmg), _is_player(is_player) {
    std::string path = is_player ? "bullet.png" : "bullet-enemy.png";
    sf::Texture tex;
    tex.loadFromFile("asset/sprites/" + path);
    _sprite.setTexture(tex);
    _sprite.setPosition(_position);
}

void Bullet::update(float delta) {
    _position += _velocity * delta;
    _sprite.setPosition(_position);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(_sprite);
}

sf::Vector2f Bullet::getPosition() const { return _position; }

int Bullet::getDmg() const { return _dmg; }

bool Bullet::isPlayer() const { return _is_player; }

const sf::Sprite& Bullet::getSprite() const { return _sprite; }
