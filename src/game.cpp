#include "../header/game.h"
#include "../header/miner.h"
#include "../header/engineer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

Game::Game() : _window(sf::VideoMode(800, 600), "Space Venture"), _state(GameState::PLANET), _minigame(nullptr), _travel_timer(0.f), _encountered(false), _destination(nullptr), _action_timer(0.f), _action_duration(0.f) {
    srand(static_cast<unsigned int>(time(nullptr)));
    _font.loadFromFile("asset/fonts/roboto.ttf");
    _message.setFont(_font);
    _message.setCharacterSize(24);
    _message.setFillColor(sf::Color::White);
    _message.setPosition(200, 50);
    _status.setFont(_font);
    _status.setCharacterSize(18);
    _status.setFillColor(sf::Color::White);
    _status.setPosition(600, 10);
    sf::Texture space_tex;
    space_tex.loadFromFile("asset/sprites/space.png");
    _space_background.setTexture(space_tex);
    init();
}

Game::~Game() {
    delete _ship;
    delete _starting_region;
    if (_minigame) delete _minigame;
}

void Game::init() {
    _starting_region = new Region("Starting Region", false, 1);
    setupRegion();
    _ship = new Spaceship("Player Ship");
    _ship->setRegion(_starting_region);
    _ship->setCurrentPlanet(_starting_region->getPlanets()[0]);
    updatePlanetScreen();
}

void Game::setupRegion() {
    Planet* start = new Planet("Start", _starting_region);
    start->loadSprite("asset/sprites/space.png");
    Planet* kepler_a = new Planet("Kepler-A", _starting_region);
    kepler_a->loadSprite("asset/sprites/kepler-a.png");
    kepler_a->addResource(new Resource("Elixir", false, 50));
    Planet* kepler_b = new Planet("Kepler-B", _starting_region);
    kepler_b->loadSprite("asset/sprites/kepler-b.png");
    kepler_b->addResource(new Resource("Mithrol", false, 100));
    _starting_region->addPlanet(start);
    _starting_region->addPlanet(kepler_a);
    _starting_region->addPlanet(kepler_b);
}

void Game::run() {
    while (_window.isOpen()) {
        float delta = _delta_clock.restart().asSeconds();
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) _window.close();
            if (_state == GameState::MINIGAME) {
                _minigame->handleInput(event);
            }
            if (event.type == sf::Event::MouseButtonPressed && (_state == GameState::PLANET || _state == GameState::JOB_CENTRE)) {
                sf::Vector2f mouse = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
                for (auto& btn : _buttons) {
                    if (btn.handleClick(mouse)) break;
                }
            }
        }
        sf::Vector2f mouse = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
        for (auto& btn : _buttons) btn.updateHover(mouse);
        if (_state == GameState::TRAVEL) {
            _travel_timer += delta;
            if (_travel_timer > 5.f) {
                _ship->travel(_starting_region, _destination);
                _state = GameState::PLANET;
                updatePlanetScreen();
            }
            if (!_encountered && _travel_timer > 2.f && (rand() % 100 < _starting_region->getDangerLevel() * 10)) {
                _encountered = true;
                _minigame = new Minigame(_ship, _starting_region->generateThreats());
                _state = GameState::MINIGAME;
            }
        }
        if (_state == GameState::MINIGAME) {
            _minigame->update(delta);
            if (_minigame->isDone()) {
                if (_minigame->survived()) {
                    _state = GameState::TRAVEL;
                } else {
                    _state = GameState::PLANET;
                    updatePlanetScreen();
                }
                delete _minigame;
                _minigame = nullptr;
            }
        }
        if (_state == GameState::ACTION) {
            _action_timer += delta;
            if (_action_timer > _action_duration) {
                if (_action_name.find("Mining") == 0) {
                    _ship->collectResources(_action_resource, _ship->countMiners(), _ship->getEquipmentLvl());
                } else if (_action_name == "Repairing") {
                    _ship->getCurrentPlanet()->repairShip(_ship, _ship->countEngineers());
                } else if (_action_name == "Upgrading Weapon") {
                    _ship->getCurrentPlanet()->getUpgradeStation()->upgradeWeapon(_ship, _ship->countEngineers());
                } else if (_action_name == "Upgrading Shield") {
                    _ship->getCurrentPlanet()->getUpgradeStation()->upgradeShield(_ship, _ship->countEngineers());
                } else if (_action_name == "Upgrading Equipment") {
                    _ship->getCurrentPlanet()->getUpgradeStation()->upgradeEquipment(_ship, _ship->countEngineers());
                }
                _state = GameState::PLANET;
                updatePlanetScreen();
            }
        }
        _window.clear();
        if (_state == GameState::TRAVEL) {
            _window.draw(_space_background);
            _message.setString("Traveling...");
            _window.draw(_message);
        } else if (_state == GameState::MINIGAME) {
            _minigame->draw(_window);
        } else {
            _window.draw(_background);
            _window.draw(_message);
            _window.draw(_status);
            for (auto& btn : _buttons) btn.draw(_window);
            if (_state == GameState::ACTION) {
                _message.setString(_action_name + " in progress...");
                _window.draw(_message);
            }
        }
        _window.display();
    }
}

void Game::updatePlanetScreen() {
    _background = _ship->getCurrentPlanet()->getSprite();
    _message.setString("You are on " + _ship->getCurrentPlanet()->getName());
    _buttons.clear();
    addButton(sf::Vector2f(10, 500), "Travel", [this]() {
        Planet* current = _ship->getCurrentPlanet();
        Planet* next;
        if (current == _starting_region->getPlanets()[0]) next = _starting_region->getPlanets()[1];
        else if (current == _starting_region->getPlanets()[1]) next = _starting_region->getPlanets()[2];
        else next = _starting_region->getPlanets()[0];
        _destination = next;
        _travel_timer = 0.f;
        _encountered = false;
        _state = GameState::TRAVEL;
    });
    if (!_ship->getCurrentPlanet()->getResources().empty()) {
        std::string res_type = _ship->getCurrentPlanet()->getResources()[0]->getType();
        std::string res_icon = res_type == "Elixir" ? "elixir.png" : "mithrol-pump.png";
        addButton(sf::Vector2f(10, 10), "Collect Resources", [this, res_type]() {
            int miners = _ship->countMiners();
            if (miners > 0) {
                _action_duration = 30.f / miners;
                _action_timer = 0.f;
                _action_name = "Mining " + res_type;
                _action_resource = res_type;
                _state = GameState::ACTION;
            }
        }, res_icon);
    }
    addButton(sf::Vector2f(10, 100), "Refuel", [this]() {
        int amount = 50;
        _ship->getCurrentPlanet()->refuel(amount, _ship);
        updateStatus();
    }, "station-refuel.png");
    addButton(sf::Vector2f(10, 190), "Repair", [this]() {
        int engineers = _ship->countEngineers();
        float damage = static_cast<float>(_ship->getShield()->getHp() - _ship->getShield()->getCurrentHp());
        if (engineers > 0 && damage > 0) {
            _action_duration = damage / (engineers * 5.f);
            _action_timer = 0.f;
            _action_name = "Repairing";
            _state = GameState::ACTION;
        }
    }, "station-repair.png");
    addButton(sf::Vector2f(10, 280), "Upgrade Weapon", [this]() {
        std::string res_req = "Elixir";
        int cost = _ship->getWeapon()->getLvl() * 10;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 20.f / engineers;
            _action_timer = 0.f;
            _action_name = "Upgrading Weapon";
            _state = GameState::ACTION;
        }
    }, "station-upgrade.png");
    addButton(sf::Vector2f(10, 370), "Upgrade Shield", [this]() {
        std::string res_req = "Mithrol";
        int cost = _ship->getShield()->getLvl() * 10;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 20.f / engineers;
            _action_timer = 0.f;
            _action_name = "Upgrading Shield";
            _state = GameState::ACTION;
        }
    }, "station-upgrade.png");
    addButton(sf::Vector2f(10, 460), "Upgrade Equipment", [this]() {
        std::string res_req = "Elixir";
        int cost = _ship->getEquipmentLvl() * 5;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 20.f / engineers;
            _action_timer = 0.f;
            _action_name = "Upgrading Equipment";
            _state = GameState::ACTION;
        }
    }, "station-upgrade.png");
    addButton(sf::Vector2f(10, 550), "Job Centre", [this]() {
        _state = GameState::JOB_CENTRE;
        updateJobScreen();
    }, "station-job.png");
    addButton(sf::Vector2f(400, 10), "Sell Resources", [this]() {
        for (auto c : _ship->getCargo()) {
            _ship->sellResource(c->getType(), c->getAmount());
        }
        updateStatus();
    });
    updateStatus();
}

void Game::updateJobScreen() {
    _message.setString("Job Centre");
    _buttons.clear();
    addButton(sf::Vector2f(10, 10), "Hire Miner", [this]() {
        int id = static_cast<int>(_ship->getCrew().size()) + 1;
        Miner* m = new Miner(id, 1, 50, 5);
        _ship->getCurrentPlanet()->getJobCentre()->hireCrew(m, _ship);
        updateStatus();
    });
    addButton(sf::Vector2f(10, 100), "Hire Engineer", [this]() {
        int id = static_cast<int>(_ship->getCrew().size()) + 1;
        Engineer* e = new Engineer(id, 1, 50, 5);
        _ship->getCurrentPlanet()->getJobCentre()->hireCrew(e, _ship);
        updateStatus();
    });
    addButton(sf::Vector2f(10, 190), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
    updateStatus();
}

void Game::updateStatus() {
    std::stringstream ss;
    ss << "Fuel: " << _ship->getFuel() << "\n"
       << "Money: " << _ship->getMoney() << "\n"
       << "HP: " << _ship->getShield()->getCurrentHp() << "/" << _ship->getShield()->getHp() << "\n"
       << "Miners: " << _ship->countMiners() << "\n"
       << "Engineers: " << _ship->countEngineers() << "\n"
       << "Cargo:\n";
    for (auto c : _ship->getCargo()) {
        ss << c->getType() << ": " << c->getAmount() << "\n";
    }
    _status.setString(ss.str());
}

void Game::addButton(sf::Vector2f pos, std::string label, std::function<void()> on_click, std::string icon) {
    _buttons.emplace_back(pos, sf::Vector2f(300,80), label, _font, on_click, icon);
}
