#include "../header/asteroid.h"

Asteroid::Asteroid(int lvl, sf::Vector2f pos)
    : Threat(lvl * 30, lvl * 10, lvl, pos, sf::Vector2f(0.f, 3.f)) {
    // Assume circle shape for asteroid
    _sprite.setTexture(sf::Texture());  // Placeholder
}

void Asteroid::draw(sf::RenderWindow& window) {
    window.draw(_sprite);
}

void Asteroid::attack() {
    // No shoot, only collide
}
