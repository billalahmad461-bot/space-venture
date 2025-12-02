#ifndef END_GAME_H
#define END_GAME_H

#include <SFML/Graphics.hpp>

class EndGame {
private:
    sf::Text _win_message;
    sf::Sprite _family_sprite;
    sf::Font& _font;

public:
    EndGame(sf::Font& font);
    void draw(sf::RenderWindow& window);
};

#endif
