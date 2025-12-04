#include "../../header/game/end-game.h"
EndGame::EndGame(sf::Font& font) : _font(font) {
    _win_message.setFont(_font);
    _win_message.setString("Reunited with family! You win!");
    _win_message.setCharacterSize(40);
    _win_message.setFillColor(sf::Color::Green);
    _win_message.setPosition(200, 250);
    _family_texture.loadFromFile("asset/sprites/family.png");
    _family_sprite.setTexture(_family_texture);
    _family_sprite.setPosition(300, 300);
}
void EndGame::draw(sf::RenderWindow& window) {
    window.draw(_win_message);
    window.draw(_family_sprite);
}
