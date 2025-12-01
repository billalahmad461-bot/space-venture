#ifndef THREAT_H
#define THREAT_H

#include <SFML/Graphics.hpp>

class Threat {
protected:
    int _hp;
    int _dmg;
    int _lvl;
    sf::Vector2f _position;
    sf::Vector2f _velocity;
    sf::Sprite _sprite;  // For rendering in minigame

public:
    Threat(int hp, int dmg, int lvl, sf::Vector2f pos, sf::Vector2f vel);
    virtual ~Threat() = default;
    int getHp() const;
    int getDmg() const;
    int getLvl() const;
    sf::Vector2f getPosition() const;
    void update();
    void takeDamage(int dmg);
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void attack() = 0;  // Virtual for specific behavior
    const sf::Sprite& getSprite() const;
};

#endif
