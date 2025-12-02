#include "../header/button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string label, sf::Font& font, std::function<void()> on_click, std::string icon_path)
    : _on_click(on_click), _is_hover(false) {
    sf::Texture tex_bg;
    tex_bg.loadFromFile("asset/sprites/button-normal.png");
    _background_sprite.setTexture(tex_bg);
    _background_sprite.setPosition(pos);
    _background_sprite.setScale(size.x / static_cast<float>(tex_bg.getSize().x), size.y / static_cast<float>(tex_bg.getSize().y));
    _text.setFont(font);
    _text.setString(label);
    _text.setCharacterSize(20);
    _text.setFillColor(sf::Color::White);
    _text.setOrigin(_text.getLocalBounds().width / 2.f, _text.getLocalBounds().height / 2.f);
    if (!icon_path.empty()) {
        sf::Texture tex_icon;
        tex_icon.loadFromFile("asset/sprites/" + icon_path);
        _icon.setTexture(tex_icon);
        _icon.setPosition(pos.x + 10, pos.y + (size.y - tex_icon.getSize().y * 0.5f) / 2);
        _icon.setScale(0.5f, 0.5f);
        _text.setPosition(pos.x + size.x / 2 + 40, pos.y + size.y / 2);
    } else {
        _text.setPosition(pos.x + size.x / 2, pos.y + size.y / 2);
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(_background_sprite);
    if (_icon.getTexture()) window.draw(_icon);
    window.draw(_text);
}

bool Button::handleClick(sf::Vector2f mouse_pos) {
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
