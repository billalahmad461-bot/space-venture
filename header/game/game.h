#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "../entities/spaceship.h"
#include "../world/region.h"
#include "../ui/button.h"
#include "minigame.h"
#include "../ui/travel-animatic.h"
#include "../ui/message-log.h"
#include "end-game.h"
#include <vector>
#include <functional>
#include <string>
#include <map>
#include <sstream>
enum class GameState { START_MENU, PLANET, TRAVEL, MINIGAME, ACTION, JOB_CENTRE, TRAVEL_SELECT, UPGRADE_SELECT, WIN, LOSE, CARGO_MENU };
class Game {
private:
    sf::Texture _space_texture;
    sf::RenderWindow _window;
    sf::Font _font;
    sf::Text _message;
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
    sf::Texture _health_textures[5];
    sf::Sprite _health_sprite;
    sf::Texture _fuel_textures[5];
    sf::Sprite _fuel_sprite;
    sf::Texture _money_tex;
    sf::Sprite _money_spr;
    sf::Text _money_txt;
    sf::Texture _miner_tex;
    sf::Sprite _miner_spr;
    sf::Text _miner_txt;
    sf::Texture _engineer_tex;
    sf::Sprite _engineer_spr;
    sf::Text _engineer_txt;
    sf::Texture _cargo_tex;
    sf::Sprite _cargo_spr;
    sf::Texture _weapon_tex;
    sf::Sprite _weapon_spr;
    sf::Text _weapon_txt;
    sf::Texture _shield_tex;
    sf::Sprite _shield_spr;
    sf::Text _shield_txt;
    sf::Texture _equipment_tex;
    sf::Sprite _equipment_spr;
    sf::Text _equipment_txt;
    sf::Texture _start_bg_tex;
    sf::Sprite _start_bg_spr;
    void init();
    void setupRegions();
    void updatePlanetScreen();
    void updateJobScreen();
    void updateUpgradeSelectScreen();
    void updateCargoScreen();
    void updateStartMenu();
    void updateStatus();
    void addButton(sf::Vector2f pos, std::string label, std::function<void()> on_click, std::string icon = "");
    void updateTravelSelectScreen();
    void checkWinCondition();
    void handleActionComplete();
    void showMessage(std::string msg);
    void drawStatus();
public:
    Game();
    ~Game();
    void run();
};
#endif
