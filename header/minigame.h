#ifndef MINIGAME_H
#define MINIGAME_H

#include <SFML/Graphics.hpp>
#include "spaceship.h"
#include "threat.h"
#include "bullet.h"

class Minigame {
private:
    Spaceship* _ship;
    std::vector<Threat*> _threats;
    std::vector<Bullet*> _bullets;
    sf::Sprite _background;

public:
    Minigame(Spaceship* ship, std::vector<Threat*> threats);
    ~Minigame();
    bool run(sf::RenderWindow& window);  // Returns true if survived
    void update();
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event);
};

#endif
