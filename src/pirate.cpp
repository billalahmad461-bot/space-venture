#include "../header/pirate.h"
#include <cmath>

Pirate::Pirate(int lvl, sf::Vector2f pos) : Threat(lvl * 20, lvl * 5, lvl, pos, sf::Vector2f(0.f, 0.f)), _direction(1.f) {
    _texture.loadFromFile("asset/sprites/threats/pirate.png");
    _sprite.setTexture(_texture);
    _sprite.setPosition(pos);
}

void Pirate::update(float delta) {
    Threat::update(delta);
    _position.x += 100.f * _direction * delta;
    if (_position.x < 0 || _position.x > 800 - _texture.getSize().x) {
        _direction *= -1;
    }
    _sprite.setPosition(_position);
}

void Pirate::attack(std::vector<Bullet*>& bullets, sf::Vector2f target_pos) {
    if (_shoot_clock.getElapsedTime().asSeconds() > 1.f) {
        sf::Vector2f bullet_pos = _position + sf::Vector2f(_texture.getSize().x / 2.f, _texture.getSize().y);
        sf::Vector2f dir = target_pos - _position;
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (length > 0) dir /= length;
        bullets.push_back(new Bullet(bullet_pos, dir * 200.f, _dmg, false));
        _shoot_clock.restart();
    }
}
