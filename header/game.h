#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "spaceship.h"
#include "region.h"
#include "button.h"
#include "minigame.h"
#include <vector>
#include <functional>
#include <string>

enum class GameState { PLANET, TRAVEL, MINIGAME, ACTION, JOB_CENTRE };

class Game {
private:
    sf::RenderWindow _window;
    sf::Font _font;
    sf::Text _message;
    sf::Text _status;
    sf::Sprite _background;
    sf::Sprite _space_background;
    Spaceship* _ship;
    Region* _starting_region;
    GameState _state;
    std::vector<Button> _buttons;
    Minigame* _minigame;
    sf::Clock _delta_clock;
    float _travel_timer;
    bool _encountered;
    Planet* _destination;
    float _action_timer;
    float _action_duration;
    std::string _action_name;
    std::string _action_resource;
    void init();
    void setupRegion();
    void updatePlanetScreen();
    void updateJobScreen();
    void updateStatus();
    void addButton(sf::Vector2f pos, std::string label, std::function<void()> on_click, std::string icon = "");

public:
    Game();
    ~Game();
    void run();
};

#endif
