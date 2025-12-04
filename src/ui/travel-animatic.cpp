#include "../../header/ui/travel-animatic.h"
TravelAnimatic::TravelAnimatic() {
    _texture.loadFromFile("asset/sprites/backgrounds/space.png");
    _anim_sprite.setTexture(_texture);
    _anim_sprite.setPosition(0, 0);
    _ship_texture.loadFromFile("asset/sprites/spaceship/spaceship-main.png");
    _ship_sprite.setTexture(_ship_texture);
    _ship_sprite.setPosition(0, 0);
}
void TravelAnimatic::update(float delta) {
}
void TravelAnimatic::draw(sf::RenderWindow& window) {
    window.draw(_anim_sprite);
    window.draw(_ship_sprite);
}
