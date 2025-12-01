#ifndef PIRATE_H
#define PIRATE_H

#include "threat.h"

class Pirate : public Threat {
public:
    Pirate(int lvl, sf::Vector2f pos);
    void draw(sf::RenderWindow& window) override;
    void attack() override;  // Pirates shoot
};

#endif
