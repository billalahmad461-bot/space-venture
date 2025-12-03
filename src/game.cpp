#include "../header/game.h"
#include "../header/miner.h"
#include "../header/engineer.h"
#include "../header/region-unlock.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

Game::Game() : _window(sf::VideoMode(900, 600), "Space Venture"), _state(GameState::PLANET), _minigame(nullptr), _travel_timer(0.f), _encountered(false), _destination(nullptr), _action_timer(0.f), _action_duration(0.f) {
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
    _space_texture.loadFromFile("asset/sprites/space.png");
    _space_background.setTexture(_space_texture);
    _message_log = new MessageLog(_font);
    _travel_anim = new TravelAnimatic();
    _end_screen = new EndGame(_font);
    init();
}

Game::~Game() {
    for (auto r : _regions) delete r;
    delete _ship;
    if (_minigame) delete _minigame;
    delete _message_log;
    delete _travel_anim;
    delete _end_screen;
}

void Game::init() {
    setupRegions();
    _ship = new Spaceship("Player Ship");
    _ship->setRegion(_regions[0]);
    _ship->setCurrentPlanet(_regions[0]->getPlanets()[0]);
    updatePlanetScreen();
}

void Game::setupRegions() {
    _regions.push_back(new Region("Starting Region", false, 1, new RegionUnlockRequirement(1, 1)));
    Planet* start_p = new Planet("StartPlanet", _regions[0]);
    start_p->addResource(new Resource("Iron", 1, 20));
    start_p->loadSprite("asset/sprites/space.png");
    _regions[0]->addPlanet(start_p);
    Planet* kepler_a = new Planet("Kepler-A", _regions[0]);
    kepler_a->addResource(new Resource("Elixir", 1, 50));
    kepler_a->loadSprite("asset/sprites/kepler-a.png");
    _regions[0]->addPlanet(kepler_a);
    Planet* kepler_b = new Planet("Kepler-B", _regions[0]);
    kepler_b->addResource(new Resource("Mithrol", 1, 100));
    kepler_b->loadSprite("asset/sprites/kepler-b.png");
    _regions[0]->addPlanet(kepler_b);

    _regions.push_back(new Region("Second Region", true, 2, new RegionUnlockRequirement(2, 2)));
    Planet* mid1 = new Planet("MidPlanet1", _regions[1]);
    mid1->addResource(new Resource("Adamantium", 2, 150));
    mid1->loadSprite("asset/sprites/station-job-background.png");
    _regions[1]->addPlanet(mid1);
    Planet* mid2 = new Planet("MidPlanet2", _regions[1]);
    mid2->addResource(new Resource("Plasma", 2, 200));
    mid2->loadSprite("asset/sprites/station-upgrade-background.png");
    _regions[1]->addPlanet(mid2);

    _regions.push_back(new Region("Final Region", true, 3, new RegionUnlockRequirement(3, 3)));
    Planet* home = new Planet("HomePlanet", _regions[2]);
    home->addResource(new Resource("Crystal", 3, 300));
    home->loadSprite("asset/sprites/win-screen.png");
    _regions[2]->addPlanet(home);
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
            if (event.type == sf::Event::MouseButtonPressed && (_state == GameState::PLANET || _state == GameState::JOB_CENTRE || _state == GameState::TRAVEL_SELECT || _state == GameState::UPGRADE_SELECT)) {
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
            _travel_anim->update(delta);
            if (_travel_timer > 5.f) {
                _ship->travel(_destination->getRegion(), _destination);
                _state = GameState::PLANET;
                updatePlanetScreen();
            }
            if (!_encountered && _travel_timer > 2.f && (rand() % 100 < _ship->getRegion()->getDangerLevel() * 10)) {
                _encountered = true;
                _minigame = new Minigame(_ship, _ship->getRegion()->generateThreats());
                _state = GameState::MINIGAME;
            }
        }
        if (_state == GameState::MINIGAME) {
            _minigame->update(delta);
            if (_minigame->isDone()) {
                if (_minigame->survived()) {
                    _state = GameState::TRAVEL;
                } else {
                    _state = GameState::LOSE;
                    // Penalty
                }
                delete _minigame;
                _minigame = nullptr;
            }
        }
        if (_state == GameState::ACTION) {
            _action_timer += delta;
            if (_action_timer > _action_duration) {
                handleActionComplete();
                checkWinCondition();
                _state = GameState::PLANET;
                updatePlanetScreen();
            }
        }
        if (_state == GameState::TRAVEL_SELECT) updateTravelSelectScreen();
        if (_state == GameState::UPGRADE_SELECT) updateUpgradeSelectScreen();
        _window.clear();
        if (_state == GameState::TRAVEL) {
            _travel_anim->draw(_window);
            _message.setString("Traveling...");
            _window.draw(_message);
        } else if (_state == GameState::MINIGAME) {
            _minigame->draw(_window);
        } else if (_state == GameState::WIN) {
            _end_screen->draw(_window);
        } else if (_state == GameState::LOSE) {
            _message.setString("Game Over!");
            _window.draw(_message);
        } else {
            _window.draw(_background);
            _window.draw(_message);
            _window.draw(_status);
            for (auto& btn : _buttons) btn.draw(_window);
            if (_state == GameState::ACTION) {
                _message.setString(_action_name + " in progress...");
                _window.draw(_message);
            }
            _message_log->draw(_window);
        }
        _window.display();
    }
}

void Game::updatePlanetScreen() {
    _background = _ship->getCurrentPlanet()->getSprite();
    _message.setString("You are on " + _ship->getCurrentPlanet()->getName());
    _buttons.clear();
    addButton(sf::Vector2f(10, 500), "Travel", [this]() {
        _state = GameState::TRAVEL_SELECT;
        updateTravelSelectScreen();
    });
    bool has_miners = _ship->countMiners() > 0;
    Button& collect_btn = _buttons.emplace_back(sf::Vector2f(10, 10), sf::Vector2f(300,80), "Collect Resources", _font, [this]() {
        _action_duration = 60.f / _ship->getTotalMiningRate();
        _action_name = "Mining";
        _action_resource = _ship->getCurrentPlanet()->getUniqueResource()->getType();
        _state = GameState::ACTION;
    });
    collect_btn.setEnabled(has_miners && _ship->getEquipment()->getLvl() >= _ship->getCurrentPlanet()->getUniqueResource()->getReqEquipLvl());
    addButton(sf::Vector2f(10, 100), "Refuel", [this]() {
        int amount = 50;
        _ship->getCurrentPlanet()->refuel(amount, _ship);
        updateStatus();
    }, "station-refuel-icon.png");
    addButton(sf::Vector2f(10, 190), "Repair", [this]() {
        int engineers = _ship->countEngineers();
        float damage = static_cast<float>(_ship->getShield()->getHp() - _ship->getShield()->getCurrentHp());
        if (engineers > 0 && damage > 0) {
            _action_duration = damage / _ship->getTotalEngineeringRate();
            _action_timer = 0.f;
            _action_name = "Repairing";
            _state = GameState::ACTION;
        }
    }, "station-repair-icon.png");
    addButton(sf::Vector2f(10, 280), "Upgrades", [this]() {
        _state = GameState::UPGRADE_SELECT;
        updateUpgradeSelectScreen();
    }, "station-upgrade-icon.png");
    addButton(sf::Vector2f(10, 460), "Job Centre", [this]() {
        _state = GameState::JOB_CENTRE;
        updateJobScreen();
    }, "station-job-icon.png");
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
    addButton(sf::Vector2f(10, 200), "Upgrade Miner", [this]() {
        // Assume upgrade first miner, or loop to find
        for (auto c : _ship->getCrew()) {
            if (c->getType() == "miner") {
                _ship->getCurrentPlanet()->getJobCentre()->upgradeCrew(c->getId(), _ship);
                break;
            }
        }
        updateStatus();
    });
    addButton(sf::Vector2f(10, 290), "Upgrade Engineer", [this]() {
        for (auto c : _ship->getCrew()) {
            if (c->getType() == "engineer") {
                _ship->getCurrentPlanet()->getJobCentre()->upgradeCrew(c->getId(), _ship);
                break;
            }
        }
        updateStatus();
    });
    addButton(sf::Vector2f(10, 380), "Back", [this]() {
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

void Game::updateTravelSelectScreen() {
    _buttons.clear();
    for (auto reg : _regions) {
        if (!reg->isLocked() || _ship->canUnlockRegion(reg)) {
            for (auto pl : reg->getPlanets()) {
                if (pl != _ship->getCurrentPlanet()) {
                    addButton(sf::Vector2f(10, 10 + _buttons.size() * 90), pl->getName(), [this, pl, reg]() {
                        if (reg->isLocked()) {
                            if (_ship->canUnlockRegion(reg)) {
                                reg->setLocked(false);
                            } else {
                                showMessage("Region locked! Upgrade more.");
                                return;
                            }
                        }
                        int cost = (_ship->getRegion() == reg) ? 20 : 50;
                        if (_ship->getFuel() >= cost) {
                            _destination = pl;
                            _travel_timer = 0.f;
                            _encountered = false;
                            _state = GameState::TRAVEL;
                        } else {
                            showMessage("Insufficient fuel!");
                        }
                    });
                }
            }
        } else {
            showMessage("Region locked! Upgrade more.");
        }
    }
    addButton(sf::Vector2f(10, 10 + _buttons.size() * 90), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
}

void Game::updateUpgradeSelectScreen() {
    _buttons.clear();
    addButton(sf::Vector2f(10, 10), "Upgrade Weapon", [this]() {
        std::string res_req = "Elixir";
        int cost = _ship->getWeapon()->getLvl() * 10;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 20.f / _ship->getTotalEngineeringRate();
            _action_name = "Upgrading Weapon";
            _state = GameState::ACTION;
        } else {
            showMessage("Can't upgrade!");
        }
    }, "station-upgrade-icon.png");
    addButton(sf::Vector2f(10, 100), "Upgrade Shield", [this]() {
        std::string res_req = "Mithrol";
        int cost = _ship->getShield()->getLvl() * 10;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 20.f / _ship->getTotalEngineeringRate();
            _action_name = "Upgrading Shield";
            _state = GameState::ACTION;
        } else {
            showMessage("Can't upgrade!");
        }
    }, "station-upgrade-icon.png");
    addButton(sf::Vector2f(10, 190), "Upgrade Equipment", [this]() {
        std::string res_req = "Elixir";
        int cost = _ship->getEquipment()->getLvl() * 5;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 20.f / _ship->getTotalEngineeringRate();
            _action_name = "Upgrading Equipment";
            _state = GameState::ACTION;
        } else {
            showMessage("Can't upgrade!");
        }
    }, "station-upgrade-icon.png");
    addButton(sf::Vector2f(10, 280), "Upgrade Max Fuel", [this]() {
        std::string res_req = "Plasma";
        int cost = 20;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 20.f / _ship->getTotalEngineeringRate();
            _action_name = "Upgrading Max Fuel";
            _state = GameState::ACTION;
        } else {
            showMessage("Can't upgrade!");
        }
    }, "station-upgrade-icon.png");
    addButton(sf::Vector2f(10, 370), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
}

void Game::handleActionComplete() {
    if (_action_name.find("Mining") == 0) {
        _ship->collectResources(_action_resource, _ship->getEquipment()->getLvl());
    } else if (_action_name == "Repairing") {
        _ship->getCurrentPlanet()->repairShip(_ship, _ship->countEngineers());
    } else if (_action_name == "Upgrading Weapon") {
        _ship->getCurrentPlanet()->getUpgradeStation()->upgradeWeapon(_ship, _ship->countEngineers());
    } else if (_action_name == "Upgrading Shield") {
        _ship->getCurrentPlanet()->getUpgradeStation()->upgradeShield(_ship, _ship->countEngineers());
    } else if (_action_name == "Upgrading Equipment") {
        _ship->getCurrentPlanet()->getUpgradeStation()->upgradeEquipment(_ship, _ship->countEngineers());
    } else if (_action_name == "Upgrading Max Fuel") {
        _ship->getCurrentPlanet()->getUpgradeStation()->upgradeMaxFuel(_ship, _ship->countEngineers());
    }
}

void Game::checkWinCondition() {
    if (_ship->getCurrentPlanet()->getName() == "HomePlanet" &&
        _ship->getWeapon()->getLvl() >= 3 && _ship->getShield()->getLvl() >= 3 && _ship->getEquipment()->getLvl() >= 3) {
        _state = GameState::WIN;
    }
}

void Game::showMessage(std::string msg) {
    _message_log->addMessage(msg);
}
