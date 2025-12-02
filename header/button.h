#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class Button {
private:
    sf::Sprite _background_sprite;
    sf::Text _text;
    sf::Sprite _icon;
    std::function<void()> _on_click;
    bool _is_hover;

public:
    Button(sf::Vector2f pos, sf::Vector2f size, std::string label, sf::Font& font, std::function<void()> on_click, std::string icon_path = "");
    void draw(sf::RenderWindow& window);
    bool handleClick(sf::Vector2f mouse_pos);
    void updateHover(sf::Vector2f mouse_pos);
};

#endif
