#include "../header/travel-animatic.h"

TravelAnimatic::TravelAnimatic() {
    _texture.loadFromFile("asset/sprites/space.png"); // Example scrolling stars
    _anim_sprite.setTexture(_texture);
    _anim_sprite.setPosition(0, 0);
}

void TravelAnimatic::update(float delta) {
    // Simple scrolling
    sf::Vector2f pos = _anim_sprite.getPosition();
    pos.y += 100.f * delta; // Scroll down
    if (pos.y > 600) pos.y = 0;
    _anim_sprite.setPosition(pos);
}

void TravelAnimatic::draw(sf::RenderWindow& window) {
    window.draw(_anim_sprite);
}
