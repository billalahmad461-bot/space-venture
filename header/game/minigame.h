#ifndef MINIGAME_H
#define MINIGAME_H
#include <SFML/Graphics.hpp>
#include "../entities/spaceship.h"
#include "../threats/threat.h"
#include "../entities/bullet.h"
class Minigame {
private:
    sf::Texture _background_texture;
    Spaceship* _ship;
    std::vector<Threat*> _threats;
    std::vector<Bullet*> _bullets;
    sf::Sprite _background;
    bool _done;
    bool _survived;
public:
    Minigame(Spaceship* ship, std::vector<Threat*> threats);
    ~Minigame();
    void update(float delta);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event);
    bool isDone() const;
    bool survived() const;
    void reset();
};
#endif
