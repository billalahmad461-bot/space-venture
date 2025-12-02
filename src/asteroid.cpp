#include "../header/asteroid.h"

Asteroid::Asteroid(int lvl, sf::Vector2f pos)
    : Threat(lvl * 30, lvl * 10, lvl, pos, sf::Vector2f(0.f, 150.f)) {
    sf::Texture tex;
    tex.loadFromFile("asset/sprites/asteroid.png");
    _sprite.setTexture(tex);
    _sprite.setPosition(pos);
}

void Asteroid::attack(std::vector<Bullet*>& bullets, sf::Vector2f target_pos) {
}
