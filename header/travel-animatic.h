#ifndef TRAVEL_ANIMATIC_H
#define TRAVEL_ANIMATIC_H

#include <SFML/Graphics.hpp>

class TravelAnimatic {
private:
    sf::Sprite _anim_sprite;
    sf::Clock _anim_clock;
    sf::Texture _texture;

public:
    TravelAnimatic();
    void update(float delta);
    void draw(sf::RenderWindow& window);
};

#endif
