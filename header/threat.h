#ifndef THREAT_H
#define THREAT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "bullet.h"

class Threat {
protected:
    int _hp;
    int _dmg;
    int _lvl;
    sf::Vector2f _position;
    sf::Vector2f _velocity;
    sf::Sprite _sprite;

public:
    Threat(int hp, int dmg, int lvl, sf::Vector2f pos, sf::Vector2f vel);
    virtual ~Threat() = default;
    int getHp() const;
    int getDmg() const;
    int getLvl() const;
    sf::Vector2f getPosition() const;
    virtual void update(float delta);
    void takeDamage(int dmg);
    virtual void draw(sf::RenderWindow& window);
    virtual void attack(std::vector<Bullet*>& bullets, sf::Vector2f target_pos) = 0;
    const sf::Sprite& getSprite() const;
};

#endif
