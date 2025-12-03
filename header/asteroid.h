#ifndef ASTEROID_H
#define ASTEROID_H

#include "threat.h"

class Asteroid : public Threat {
private:
    sf::Texture _texture;

public:
    Asteroid(int lvl, sf::Vector2f pos);
    void attack(std::vector<Bullet*>& bullets, sf::Vector2f target_pos) override;
};

#endif
