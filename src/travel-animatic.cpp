#include "../header/travel-animatic.h"

TravelAnimatic::TravelAnimatic() {
    _texture.loadFromFile("asset/sprites/backgrounds/space.png");
    _anim_sprite.setTexture(_texture);
    _anim_sprite.setPosition(0, 0);
    _ship_texture.loadFromFile("asset/sprites/spaceship/spaceship-top.png");
    _ship_sprite.setTexture(_ship_texture);
    _ship_sprite.setPosition(400 - _ship_texture.getSize().x / 2.f, 500);
}

void TravelAnimatic::update(float delta) {
    // Simple scrolling
    sf::Vector2f pos = _anim_sprite.getPosition();
    pos.y += 100.f * delta; // Scroll down
    if (pos.y > 600) pos.y -= 600; // Seamless assuming texture height 600
    _anim_sprite.setPosition(pos);
}

void TravelAnimatic::draw(sf::RenderWindow& window) {
    window.draw(_anim_sprite);
    window.draw(_ship_sprite);
}
