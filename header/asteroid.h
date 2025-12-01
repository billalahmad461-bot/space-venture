#ifndef ASTEROID_H
#define ASTEROID_H

#include "threat.h"

class Asteroid : public Threat {
public:
    Asteroid(int lvl, sf::Vector2f pos);
    void draw(sf::RenderWindow& window) override;
    void attack() override;  // Asteroids collide only
};

#endif
