#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::Texture _texture;
    sf::Vector2f _position;
    sf::Vector2f _velocity;
    int _dmg;
    bool _is_player;
    sf::Sprite _sprite;

public:
    Bullet(sf::Vector2f pos, sf::Vector2f vel, int dmg, bool is_player);
    void update(float delta);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    int getDmg() const;
    bool isPlayer() const;
    const sf::Sprite& getSprite() const;
};

#endif
