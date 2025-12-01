#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
private:
    sf::RectangleShape _shape;
    sf::Text _text;
    std::function<void()> _on_click;

public:
    Button(sf::Vector2f pos, sf::Vector2f size, std::string label, sf::Font& font, std::function<void()> on_click);
    void draw(sf::RenderWindow& window);
    bool handleClick(sf::Vector2f mouse_pos);
};

#endif
