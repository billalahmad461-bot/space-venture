#include "../header/pirate.h"
#include <cmath>  // Fixed missing include for std::sqrt

Pirate::Pirate(int lvl, sf::Vector2f pos)
    : Threat(lvl * 20, lvl * 5, lvl, pos, sf::Vector2f(0.f, 100.f)) {
    sf::Texture tex;
    tex.loadFromFile("asset/sprites/pirate.png");
    _sprite.setTexture(tex);
    _sprite.setPosition(pos);
}

void Pirate::update(float delta) {
    Threat::update(delta);
    // Sinusoidal
    _position.x += sin(_position.y / 50.f) * 50.f * delta; // Example
    _sprite.setPosition(_position);
}

void Pirate::attack(std::vector<Bullet*>& bullets, sf::Vector2f target_pos) {
    if (_shoot_clock.getElapsedTime().asSeconds() > 2.f) {
        sf::Vector2f dir = target_pos - _position;
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (length > 0) dir /= length;
        bullets.push_back(new Bullet(_position, dir * 200.f, _dmg, false));
        _shoot_clock.restart();
    }
}
