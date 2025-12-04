#include "../../header/ui/button.h"
Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string label, sf::Font& font, std::function<void()> on_click, std::string icon_path) : _on_click(on_click), _is_hover(false), _enabled(true) {
    if (!icon_path.empty()) {
        _bg_texture.loadFromFile("asset/sprites/ui/icons/" + icon_path);
    } else {
        _bg_texture.loadFromFile("asset/sprites/ui/button-normal.png");
    }
    _background_sprite.setTexture(_bg_texture);
    _background_sprite.setPosition(pos);
    _background_sprite.setScale(size.x / static_cast<float>(_bg_texture.getSize().x), size.y / static_cast<float>(_bg_texture.getSize().y));
    _text.setFont(font);
    _text.setString(label);
    _text.setCharacterSize(20);
    _text.setFillColor(sf::Color::White);
    _text.setOrigin(_text.getLocalBounds().width / 2.f, _text.getLocalBounds().height / 2.f);
    _text.setPosition(pos.x + size.x / 2, pos.y + size.y / 2);
}
void Button::draw(sf::RenderWindow& window) {
    window.draw(_background_sprite);
    window.draw(_text);
}
bool Button::handleClick(sf::Vector2f mouse_pos) {
    if (!_enabled) return false;
    if (_background_sprite.getGlobalBounds().contains(mouse_pos)) {
        _on_click();
        return true;
    }
    return false;
}
void Button::updateHover(sf::Vector2f mouse_pos) {
    _is_hover = _background_sprite.getGlobalBounds().contains(mouse_pos);
    _background_sprite.setColor(_is_hover ? sf::Color(200, 200, 255) : sf::Color::White);
}
void Button::setEnabled(bool enabled) {
    _enabled = enabled;
    _background_sprite.setColor(enabled ? sf::Color::White : sf::Color(150, 150, 150));
}
