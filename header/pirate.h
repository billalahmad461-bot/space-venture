#ifndef PIRATE_H
#define PIRATE_H

#include "threat.h"

class Pirate : public Threat {
private:
    sf::Texture _texture;
    sf::Clock _shoot_clock;
    float _direction;

public:
    Pirate(int lvl, sf::Vector2f pos);
    void update(float delta);
    void attack(std::vector<Bullet*>& bullets, sf::Vector2f target_pos) override;
};

#endif
