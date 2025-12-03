#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "spaceship.h"
#include "region.h"
#include "button.h"
#include "minigame.h"
#include "travel-animatic.h"
#include "message-log.h"
#include "end-game.h"
#include <vector>
#include <functional>
#include <string>

enum class GameState { PLANET, TRAVEL, MINIGAME, ACTION, JOB_CENTRE, TRAVEL_SELECT, UPGRADE_SELECT, WIN, LOSE };

class Game {
private:
    sf::Texture _space_texture;
    sf::RenderWindow _window;
    sf::Font _font;
    sf::Text _message;
    sf::Text _status;
    sf::Sprite _background;
    sf::Sprite _space_background;
    Spaceship* _ship;
    std::vector<Region*> _regions;
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
    MessageLog* _message_log;
    TravelAnimatic* _travel_anim;
    EndGame* _end_screen;
    Planet* _selected_planet;
    void init();
    void setupRegions();
    void updatePlanetScreen();
    void updateJobScreen();
    void updateStatus();
    void addButton(sf::Vector2f pos, std::string label, std::function<void()> on_click, std::string icon = "");
    void updateTravelSelectScreen();
    void updateUpgradeSelectScreen();
    void checkWinCondition();
    void handleActionComplete();
    void showMessage(std::string msg);

public:
    Game();
    ~Game();
    void run();
};

#endif
