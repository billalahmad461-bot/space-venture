#include "../header/button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string label, sf::Font& font, std::function<void()> on_click)
    : _on_click(on_click) {
    _shape.setPosition(pos);
    _shape.setSize(size);
    _shape.setFillColor(sf::Color::Blue);
    _text.setFont(font);
    _text.setString(label);
    _text.setPosition(pos.x + 10, pos.y + 10);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(_shape);
    window.draw(_text);
}

bool Button::handleClick(sf::Vector2f mouse_pos) {
    if (_shape.getGlobalBounds().contains(mouse_pos)) {
        _on_click();
        return true;
    }
    return false;
}
