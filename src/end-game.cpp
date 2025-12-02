#include "../header/end-game.h"

EndGame::EndGame(sf::Font& font) : _font(font) {
    _win_message.setFont(_font);
    _win_message.setString("Reunited with family! You win!");
    _win_message.setCharacterSize(40);
    _win_message.setFillColor(sf::Color::Green);
    _win_message.setPosition(200, 250);

    sf::Texture tex;
    tex.loadFromFile("asset/sprites/family.png"); // Assume asset exists
    _family_sprite.setTexture(tex);
    _family_sprite.setPosition(300, 300);
}

void EndGame::draw(sf::RenderWindow& window) {
    window.draw(_win_message);
    window.draw(_family_sprite);
}
