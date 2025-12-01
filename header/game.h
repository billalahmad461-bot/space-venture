#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "spaceship.h"
#include "region.h"
#include "button.h"
#include "minigame.h"

enum class GameState { PLANET, TRAVEL, MINIGAME };

class Game {
private:
    sf::RenderWindow _window;
    sf::Font _font;
    sf::Text _message;
    sf::Sprite _background;
    Spaceship* _ship;
    Region* _starting_region;
    GameState _state;
    std::vector<Button> _buttons;
    void init();
    void setupRegion();
    void updatePlanetScreen();
    void addButton(sf::Vector2f pos, std::string label, std::function<void()> on_click);

public:
    Game();
    void run();
};

#endif
