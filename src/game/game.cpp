#include "../../header/game/game.h"
#include "../../header/crew/miner.h"
#include "../../header/crew/engineer.h"
#include "../../header/world/region-unlock.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <cctype>

Game::Game() : _window(sf::VideoMode(900, 600), "Space Venture"), _state(GameState::START_MENU), _previous_state(GameState::START_MENU), _minigame(nullptr), _travel_timer(0.f), _encountered(false), _destination(nullptr), _previous_planet(nullptr), _action_timer(0.f), _action_duration(0.f) {
    srand(static_cast<unsigned int>(time(nullptr)));
    _font.loadFromFile("asset/fonts/roboto.ttf");
    _message.setFont(_font);
    _message.setCharacterSize(24);
    _message.setFillColor(sf::Color::White);
    _message.setPosition(200, 50);
    _space_texture.loadFromFile("asset/sprites/backgrounds/space.png");
    _space_background.setTexture(_space_texture);
    _message_log = new MessageLog(_font);
    _travel_anim = new TravelAnimatic();
    _end_screen = new EndGame(_font);
    _start_bg_tex.loadFromFile("asset/sprites/backgrounds/start-menu-background.png");
    _start_bg_spr.setTexture(_start_bg_tex);
    _menu_bg_tex.loadFromFile("asset/sprites/backgrounds/pause-menu-background.png");
    _menu_bg_spr.setTexture(_menu_bg_tex);
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
    
    // Load status textures
    _health_textures[0].loadFromFile("asset/sprites/ui/bars/health-bar0.png");
    _health_textures[1].loadFromFile("asset/sprites/ui/bars/health-bar25.png");
    _health_textures[2].loadFromFile("asset/sprites/ui/bars/health-bar50.png");
    _health_textures[3].loadFromFile("asset/sprites/ui/bars/health-bar75.png");
    _health_textures[4].loadFromFile("asset/sprites/ui/bars/health-bar100.png");
    _health_sprite.setTexture(_health_textures[4]);
    _health_sprite.setPosition(800, 10);
    
    _fuel_textures[0].loadFromFile("asset/sprites/ui/bars/fuel-bar-0.png");
    _fuel_textures[1].loadFromFile("asset/sprites/ui/bars/fuel-bar-25.png");
    _fuel_textures[2].loadFromFile("asset/sprites/ui/bars/fuel-bar-50.png");
    _fuel_textures[3].loadFromFile("asset/sprites/ui/bars/fuel-bar-75.png");
    _fuel_textures[4].loadFromFile("asset/sprites/ui/bars/fuel-bar-100.png");
    _fuel_sprite.setTexture(_fuel_textures[4]);
    _fuel_sprite.setPosition(800, 60);
    
    _money_tex.loadFromFile("asset/sprites/ui/icons/money-icon.png");
    _money_spr.setTexture(_money_tex);
    _money_spr.setPosition(800, 110);
    _money_txt.setFont(_font);
    _money_txt.setCharacterSize(18);
    _money_txt.setFillColor(sf::Color::White);
    _money_txt.setPosition(850, 110);
    
    _miner_tex.loadFromFile("asset/sprites/ui/icons/miner-icon.png");
    _miner_spr.setTexture(_miner_tex);
    _miner_spr.setPosition(800, 160);
    _miner_txt.setFont(_font);
    _miner_txt.setCharacterSize(18);
    _miner_txt.setFillColor(sf::Color::White);
    _miner_txt.setPosition(850, 160);
    
    _engineer_tex.loadFromFile("asset/sprites/ui/icons/engineer-icon.png");
    _engineer_spr.setTexture(_engineer_tex);
    _engineer_spr.setPosition(800, 210);
    _engineer_txt.setFont(_font);
    _engineer_txt.setCharacterSize(18);
    _engineer_txt.setFillColor(sf::Color::White);
    _engineer_txt.setPosition(850, 210);
    
    _cargo_tex.loadFromFile("asset/sprites/ui/icons/cargo-icon.png");
    _cargo_spr.setTexture(_cargo_tex);
    _cargo_spr.setPosition(800, 260);
    
    _weapon_tex.loadFromFile("asset/sprites/ui/icons/weapon-icon.png");
    _weapon_spr.setTexture(_weapon_tex);
    _weapon_spr.setPosition(800, 310);
    _weapon_txt.setFont(_font);
    _weapon_txt.setCharacterSize(18);
    _weapon_txt.setFillColor(sf::Color::White);
    _weapon_txt.setPosition(850, 310);
    
    _shield_tex.loadFromFile("asset/sprites/ui/icons/shield-icon.png");
    _shield_spr.setTexture(_shield_tex);
    _shield_spr.setPosition(800, 360);
    _shield_txt.setFont(_font);
    _shield_txt.setCharacterSize(18);
    _shield_txt.setFillColor(sf::Color::White);
    _shield_txt.setPosition(850, 360);
    
    _equipment_tex.loadFromFile("asset/sprites/ui/icons/equipment-icon.png");
    _equipment_spr.setTexture(_equipment_tex);
    _equipment_spr.setPosition(800, 410);
    _equipment_txt.setFont(_font);
    _equipment_txt.setCharacterSize(18);
    _equipment_txt.setFillColor(sf::Color::White);
    _equipment_txt.setPosition(850, 410);
    
    updateStatus();
    updateStartMenu();
}

void Game::setupRegions() {
    _regions.push_back(new Region("Kepler Region", false, 1, new RegionUnlockRequirement(1, 1)));
    Planet* kepler_a = new Planet("Kepler-A", _regions[0]);
    kepler_a->addResource(new Resource("Elixir", 1, 50));
    kepler_a->loadSprite("asset/sprites/planets/kepler-a.png");
    _regions[0]->addPlanet(kepler_a);
    
    Planet* kepler_b = new Planet("Kepler-B", _regions[0]);
    kepler_b->addResource(new Resource("Mithrol", 1, 100));
    kepler_b->loadSprite("asset/sprites/planets/kepler-b.png");
    _regions[0]->addPlanet(kepler_b);
    
    Planet* kepler_c = new Planet("Kepler-C", _regions[0]);
    kepler_c->addResource(new Resource("Vibranium", 1, 150));
    kepler_c->loadSprite("asset/sprites/planets/kepler-c.png");
    _regions[0]->addPlanet(kepler_c);
    
    _regions.push_back(new Region("Mid Region", true, 2, new RegionUnlockRequirement(2, 2)));
    Planet* mid1 = new Planet("Mid1", _regions[1]);
    mid1->addResource(new Resource("Adamantium", 2, 200));
    mid1->loadSprite("asset/sprites/planets/mid1.png");
    _regions[1]->addPlanet(mid1);
    
    Planet* mid2 = new Planet("Mid2", _regions[1]);
    mid2->addResource(new Resource("Uru", 2, 250));
    mid2->loadSprite("asset/sprites/planets/mid2.png");
    _regions[1]->addPlanet(mid2);
    
    _regions.push_back(new Region("Tepler Region", true, 3, new RegionUnlockRequirement(3, 3)));
    Planet* tepler_a = new Planet("Tepler-A", _regions[2]);
    tepler_a->addResource(new Resource("Crystal", 3, 300));
    tepler_a->loadSprite("asset/sprites/planets/tepler-a.png");
    _regions[2]->addPlanet(tepler_a);
}

void Game::run() {
    while (_window.isOpen()) {
        float delta = _delta_clock.restart().asSeconds();
        sf::Event event;
        
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) _window.close();
            
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
                bool handled = false;
                
                for (auto& btn : _buttons) {
                    if (btn.handleClick(mouse)) {
                        handled = true;
                        break;
                    }
                }
                
                if (!handled && (_state == GameState::PLANET || _state == GameState::ACTION || _state == GameState::JOB_CENTRE || _state == GameState::UPGRADE_SELECT || _state == GameState::TRAVEL_SELECT || _state == GameState::CARGO_MENU || _state == GameState::CREW_MINER || _state == GameState::CREW_ENGINEER || _state == GameState::EQUIPMENT_MENU || _state == GameState::REFUEL || _state == GameState::REPAIR)) {
                    if (_money_spr.getGlobalBounds().contains(mouse)) {
                        _message_log->addMessage("Money: " + std::to_string(_ship->getMoney()));
                    } else if (_miner_spr.getGlobalBounds().contains(mouse)) {
                        _crew_type = "miner";
                        _state = GameState::CREW_MINER;
                        updateCrewScreen("miner");
                    } else if (_engineer_spr.getGlobalBounds().contains(mouse)) {
                        _crew_type = "engineer";
                        _state = GameState::CREW_ENGINEER;
                        updateCrewScreen("engineer");
                    } else if (_cargo_spr.getGlobalBounds().contains(mouse)) {
                        _state = GameState::CARGO_MENU;
                        updateCargoScreen();
                    } else if (_weapon_spr.getGlobalBounds().contains(mouse)) {
                        _message_log->addMessage("Weapon Level: " + std::to_string(_ship->getWeapon()->getLvl()) + "\nDamage: " + std::to_string(_ship->getWeapon()->getDmg()) + "\nFire Rate: " + std::to_string(_ship->getWeapon()->getFireRate()));
                    } else if (_shield_spr.getGlobalBounds().contains(mouse)) {
                        _message_log->addMessage("Shield Level: " + std::to_string(_ship->getShield()->getLvl()) + "\nHP: " + std::to_string(_ship->getShield()->getHp()));
                    } else if (_equipment_spr.getGlobalBounds().contains(mouse)) {
                        _state = GameState::EQUIPMENT_MENU;
                        updateEquipmentScreen();
                    }
                }
            }
            
            if (_state == GameState::MINIGAME) {
                _minigame->handleInput(event);
            }
        }
        
        sf::Vector2f mouse = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
        for (auto& btn : _buttons) btn.updateHover(mouse);
        
        if (_state == GameState::TRAVEL) {
            _travel_timer += delta;
            _travel_anim->update(delta);
            
            if (_travel_timer > 5.f) {
                _ship->travel(_destination->getRegion(), _destination);
                _message_log->addMessage("Arrived at " + _destination->getName());
                _state = GameState::PLANET;
                updatePlanetScreen();
            }
            
            if (!_encountered && _travel_timer > 2.f && (rand() % 100 < _ship->getRegion()->getDangerLevel() * 10)) {
                _encountered = true;
                _message_log->addMessage("Enemy attacked!");
                _minigame = new Minigame(_ship, _ship->getRegion()->generateThreats());
                _state = GameState::MINIGAME;
            }
        }
        
        if (_state == GameState::MINIGAME) {
            _minigame->update(delta);
            updateStatus();
            
            if (_minigame->isDone()) {
                if (_minigame->survived()) {
                    _state = GameState::TRAVEL;
                } else {
                    _ship->setCurrentPlanet(_previous_planet);
                    _ship->getShield()->setCurrentHp(_ship->getShield()->getHp());
                    _ship->setMoney(std::max(0, _ship->getMoney() - 50));
                    _message_log->addMessage("Ship damaged! Returned to previous planet. Health restored. Lost 50 money for repairs.");
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
                handleActionComplete();
                checkWinCondition();
                _state = _previous_state;
                if (_state == GameState::REPAIR) updateRepairScreen();
                else if (_state == GameState::PLANET) updatePlanetScreen();
                // Add for other if needed
            }
        }
        
        if (_state == GameState::TRAVEL_SELECT) updateTravelSelectScreen();
        if (_state == GameState::UPGRADE_SELECT) updateUpgradeSelectScreen();
        
        _window.clear();
        
        if (_state == GameState::START_MENU) {
            _window.draw(_start_bg_spr);
        } else if (_state == GameState::TRAVEL) {
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
            for (auto& btn : _buttons) btn.draw(_window);
            
            if (_state == GameState::ACTION) {
                _message.setString(_action_name + " in progress...");
                _window.draw(_message);
            }
            
            if (_state == GameState::CARGO_MENU || _state == GameState::CREW_MINER || _state == GameState::CREW_ENGINEER || _state == GameState::EQUIPMENT_MENU || _state == GameState::JOB_CENTRE || _state == GameState::UPGRADE_SELECT || _state == GameState::REFUEL || _state == GameState::REPAIR) {
                for (auto& txt : _req_texts) _window.draw(txt);
            }
            
            if (_state == GameState::CARGO_MENU) {
                for (auto& spr : _resource_sprs) _window.draw(spr);
            }
            
            _message_log->draw(_window);
        }
        
        if (_state != GameState::START_MENU && _state != GameState::WIN && _state != GameState::LOSE) {
            bool full = (_state != GameState::MINIGAME);
            drawStatus(full);
        }
        
        _window.display();
    }
}

void Game::drawStatus(bool full) {
    _window.draw(_health_sprite);
    _window.draw(_fuel_sprite);
    
    if (full) {
        _window.draw(_money_spr);
        _window.draw(_money_txt);
        _window.draw(_miner_spr);
        _window.draw(_miner_txt);
        _window.draw(_engineer_spr);
        _window.draw(_engineer_txt);
        _window.draw(_cargo_spr);
        _window.draw(_weapon_spr);
        _window.draw(_weapon_txt);
        _window.draw(_shield_spr);
        _window.draw(_shield_txt);
        _window.draw(_equipment_spr);
        _window.draw(_equipment_txt);
    }
}

void Game::updateStartMenu() {
    _buttons.clear();
    addButton(sf::Vector2f(300, 200), "Start", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
    addButton(sf::Vector2f(300, 300), "Quit", [this]() {
        _window.close();
    });
}

void Game::updatePlanetScreen() {
    _background = _ship->getCurrentPlanet()->getSprite();
    _message.setString("You are on " + _ship->getCurrentPlanet()->getName());
    _buttons.clear();
    
    addButton(sf::Vector2f(10, 500), "Travel", [this]() {
        _previous_planet = _ship->getCurrentPlanet();
        _state = GameState::TRAVEL_SELECT;
        updateTravelSelectScreen();
    });
    
    bool has_miners = _ship->countMiners() > 0;
    Button& collect_btn = _buttons.emplace_back(sf::Vector2f(10, 10), sf::Vector2f(300,80), "Collect Resources", _font, [this]() {
        _action_duration = 300.f / _ship->getTotalMiningRate();
        _action_name = "Mining";
        _action_resource = _ship->getCurrentPlanet()->getUniqueResource()->getType();
        _state = GameState::ACTION;
    });
    collect_btn.setEnabled(has_miners && _ship->getEquipment()->getLvl() >= _ship->getCurrentPlanet()->getUniqueResource()->getReqEquipLvl());
    
    addButton(sf::Vector2f(10, 100), "", [this]() {
        _state = GameState::REFUEL;
        updateRefuelScreen();
    }, "station-refuel-icon.png");
    
    addButton(sf::Vector2f(10, 210), "", [this]() {
        _state = GameState::REPAIR;
        updateRepairScreen();
    }, "station-repair-icon.png");
    
    addButton(sf::Vector2f(10, 320), "", [this]() {
        _state = GameState::UPGRADE_SELECT;
        updateUpgradeSelectScreen();
    }, "station-upgrade-icon.png");
    
    addButton(sf::Vector2f(10, 430), "", [this]() {
        _state = GameState::JOB_CENTRE;
        updateJobScreen();
    }, "station-job-icon.png");
    
    addButton(sf::Vector2f(400, 10), "Sell All Resources", [this]() {
        for (auto c : _ship->getCargo()) {
            _ship->sellResource(c->getType(), c->getAmount());
        }
        updateStatus();
    });
    
    updateStatus();
}

void Game::updateRefuelScreen() {
    sf::Texture bg_tex;
    bg_tex.loadFromFile("asset/sprites/backgrounds/station-refuel-background.png");
    _background.setTexture(bg_tex);
    _message.setString("Refuelling Station");
    _buttons.clear();
    
    addButton(sf::Vector2f(10, 10), "Refuel 50", [this]() {
        _ship->getCurrentPlanet()->refuel(50, _ship);
        updateStatus();
        showMessage("Refuelled 50 fuel.");
    });
    
    addButton(sf::Vector2f(10, 100), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
}

void Game::updateRepairScreen() {
    sf::Texture bg_tex;
    bg_tex.loadFromFile("asset/sprites/backgrounds/station-repair-background.png");
    _background.setTexture(bg_tex);
    _message.setString("Repair Station");
    _buttons.clear();
    
    addButton(sf::Vector2f(10, 10), "Repair", [this]() {
        int engineers = _ship->countEngineers();
        float damage = static_cast<float>(_ship->getShield()->getHp() - _ship->getShield()->getCurrentHp());
        if (engineers > 0 && damage > 0) {
            _action_duration = damage / _ship->getTotalEngineeringRate() * 5.f;
            _action_timer = 0.f;
            _action_name = "Repairing";
            _previous_state = GameState::REPAIR;
            _state = GameState::ACTION;
        } else {
            showMessage("No need or can't repair.");
        }
    });
    
    addButton(sf::Vector2f(10, 100), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
}

void Game::updateJobScreen() {
    sf::Texture bg_tex;
    bg_tex.loadFromFile("asset/sprites/backgrounds/station-job-background.png");
    _background.setTexture(bg_tex);
    _message.setString("Job Centre");
    _buttons.clear();
    _req_texts.clear();
    
    addButton(sf::Vector2f(10, 10), "Hire Miner", [this]() {
        int id = static_cast<int>(_ship->getCrew().size()) + 1;
        Miner* m = new Miner(id, 1, 50, 5);
        _ship->getCurrentPlanet()->getJobCentre()->hireCrew(m, _ship);
        updateStatus();
    });
    
    sf::Text req;
    req.setFont(_font);
    req.setString("Cost: 50 money");
    req.setPosition(320, 10);
    _req_texts.push_back(req);
    
    addButton(sf::Vector2f(10, 100), "Hire Engineer", [this]() {
        int id = static_cast<int>(_ship->getCrew().size()) + 1;
        Engineer* e = new Engineer(id, 1, 50, 5);
        _ship->getCurrentPlanet()->getJobCentre()->hireCrew(e, _ship);
        updateStatus();
    });
    
    req.setString("Cost: 50 money");
    req.setPosition(320, 100);
    _req_texts.push_back(req);
    
    addButton(sf::Vector2f(10, 190), "Upgrade Miner", [this]() {
        // Assume upgrade first miner, or loop to find
        for (auto c : _ship->getCrew()) {
            if (c->getType() == "miner") {
                _ship->getCurrentPlanet()->getJobCentre()->upgradeCrew(c->getId(), _ship);
                break;
            }
        }
        updateStatus();
    });
    
    req.setString("Cost: 20 * lvl money");
    req.setPosition(320, 190);
    _req_texts.push_back(req);
    
    addButton(sf::Vector2f(10, 280), "Upgrade Engineer", [this]() {
        for (auto c : _ship->getCrew()) {
            if (c->getType() == "engineer") {
                _ship->getCurrentPlanet()->getJobCentre()->upgradeCrew(c->getId(), _ship);
                break;
            }
        }
        updateStatus();
    });
    
    req.setString("Cost: 20 * lvl money");
    req.setPosition(320, 280);
    _req_texts.push_back(req);
    
    addButton(sf::Vector2f(10, 370), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
    
    updateStatus();
}

void Game::updateUpgradeSelectScreen() {
    sf::Texture bg_tex;
    bg_tex.loadFromFile("asset/sprites/backgrounds/station-upgrade-background.png");
    _background.setTexture(bg_tex);
    _buttons.clear();
    _req_texts.clear();
    
    addButton(sf::Vector2f(10, 10), "Upgrade Weapon", [this]() {
        std::string res_req = "Elixir";
        int cost = _ship->getWeapon()->getLvl() * 10;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 100.f / _ship->getTotalEngineeringRate();
            _action_name = "Upgrading Weapon";
            _state = GameState::ACTION;
        } else {
            showMessage("Can't upgrade!");
        }
    }, "station-upgrade-icon.png");
    
    sf::Text req;
    req.setFont(_font);
    req.setString("Req: Elixir " + std::to_string(_ship->getWeapon()->getLvl() * 10) + ", 1+ Engineer");
    req.setPosition(320, 10);
    _req_texts.push_back(req);
    
    addButton(sf::Vector2f(10, 100), "Upgrade Shield", [this]() {
        std::string res_req = "Mithrol";
        int cost = _ship->getShield()->getLvl() * 10;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 100.f / _ship->getTotalEngineeringRate();
            _action_name = "Upgrading Shield";
            _state = GameState::ACTION;
        } else {
            showMessage("Can't upgrade!");
        }
    }, "station-upgrade-icon.png");
    
    req.setString("Req: Mithrol " + std::to_string(_ship->getShield()->getLvl() * 10) + ", 1+ Engineer");
    req.setPosition(320, 100);
    _req_texts.push_back(req);
    
    addButton(sf::Vector2f(10, 190), "Upgrade Equipment", [this]() {
        std::string res_req = "Elixir";
        int cost = _ship->getEquipment()->getLvl() * 5;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 100.f / _ship->getTotalEngineeringRate();
            _action_name = "Upgrading Equipment";
            _state = GameState::ACTION;
        } else {
            showMessage("Can't upgrade!");
        }
    }, "station-upgrade-icon.png");
    
    req.setString("Req: Elixir " + std::to_string(_ship->getEquipment()->getLvl() * 5) + ", 1+ Engineer");
    req.setPosition(320, 190);
    _req_texts.push_back(req);
    
    addButton(sf::Vector2f(10, 280), "Upgrade Max Fuel", [this]() {
        std::string res_req = "Uru";
        int cost = 20;
        int engineers = _ship->countEngineers();
        if (_ship->consumeResource(res_req, cost) && engineers > 0) {
            _action_duration = 100.f / _ship->getTotalEngineeringRate();
            _action_name = "Upgrading Max Fuel";
            _state = GameState::ACTION;
        } else {
            showMessage("Can't upgrade!");
        }
    }, "station-upgrade-icon.png");
    
    req.setString("Req: Uru 20, 1+ Engineer");
    req.setPosition(320, 280);
    _req_texts.push_back(req);
    
    addButton(sf::Vector2f(10, 370), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
}

void Game::updateCargoScreen() {
    _background = _menu_bg_spr;
    _buttons.clear();
    _resource_sprs.clear();
    _resource_texs.clear();
    _message.setString("Cargo Management");
    
    int y = 10;
    for (auto r : _ship->getCargo()) {
        std::string lower_type = r->getType();
        std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(), ::tolower);
        std::string res_path = "asset/sprites/resources/" + lower_type + ".png";
        sf::Texture tex;
        if (tex.loadFromFile(res_path)) {
            _resource_texs.push_back(tex);
            sf::Sprite spr(_resource_texs.back());
            spr.setPosition(10, y);
            _resource_sprs.push_back(spr);
        }
        
        std::string label = r->getType() + ": " + std::to_string(r->getAmount()) + " (Value: " + std::to_string(r->getPrice()) + ")";
        addButton(sf::Vector2f(100, y), label, [](){});
        addButton(sf::Vector2f(400, y), "Sell 1", [this, r]() {
            _ship->sellResource(r->getType(), 1);
            updateStatus();
            updateCargoScreen();
        });
        y += 60; // Reduced spacing
    }
    
    addButton(sf::Vector2f(10, y), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
}

void Game::updateCrewScreen(std::string type) {
    _background = _menu_bg_spr;
    _buttons.clear();
    _message.setString(type + "s:");
    std::stringstream ss;
    int i = 1;
    
    for (auto c : _ship->getCrew()) {
        if (c->getType() == type) {
            ss << i++ << ". ID: " << c->getId() << " Level: " << c->getLvl() << "\n";
        }
    }
    
    sf::Text details(ss.str(), _font, 18);
    details.setPosition(10, 100);
    _req_texts.clear();
    _req_texts.push_back(details);
    
    addButton(sf::Vector2f(10, 500), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
}

void Game::updateEquipmentScreen() {
    _background = _menu_bg_spr;
    _buttons.clear();
    _message.setString("Equipment");
    int lvl = _ship->getEquipment()->getLvl();
    std::string req_str;
    
    if (lvl < 2) {
        req_str = "To unlock Mid Region: 100 money, 50 Elixir";
    } else if (lvl < 3) {
        req_str = "To unlock Tepler Region: 200 money, 100 Adamantium";
    } else {
        req_str = "Max level reached.";
    }
    
    sf::Text req_text(req_str, _font, 18);
    req_text.setPosition(10, 100);
    _req_texts.clear();
    _req_texts.push_back(req_text);
    
    addButton(sf::Vector2f(10, 200), "Upgrade", [this, lvl]() {
        std::string res_req;
        int money_cost, res_cost;
        if (lvl < 2) {
            res_req = "Elixir";
            money_cost = 100;
            res_cost = 50;
        } else if (lvl < 3) {
            res_req = "Adamantium";
            money_cost = 200;
            res_cost = 100;
        } else {
            showMessage("Max level!");
            return;
        }
        
        if (_ship->getMoney() >= money_cost && _ship->consumeResource(res_req, res_cost)) {
            _ship->getEquipment()->upgrade();
            _ship->setMoney(_ship->getMoney() - money_cost);
            updateStatus();
            updateEquipmentScreen();
        } else {
            showMessage("Insufficient resources!");
        }
    });
    
    addButton(sf::Vector2f(10, 500), "Back", [this]() {
        _state = GameState::PLANET;
        updatePlanetScreen();
    });
}

void Game::updateStatus() {
    auto calc_closest = [](float percent) -> int {
        std::vector<int> lvls = {0, 25, 50, 75, 100};
        int idx = 0;
        float min_d = std::abs(percent - lvls[0]);
        for (int i = 1; i < 5; ++i) {
            float d = std::abs(percent - lvls[i]);
            if (d < min_d) {
                min_d = d;
                idx = i;
            }
        }
        return idx;
    };
    
    float hp_p = static_cast<float>(_ship->getShield()->getCurrentHp()) / _ship->getShield()->getHp() * 100.f;
    _health_sprite.setTexture(_health_textures[calc_closest(hp_p)]);
    
    float fuel_p = static_cast<float>(_ship->getFuel()) / _ship->getMaxFuel() * 100.f;
    _fuel_sprite.setTexture(_fuel_textures[calc_closest(fuel_p)]);
    
    _money_txt.setString(std::to_string(_ship->getMoney()));
    _miner_txt.setString(std::to_string(_ship->countMiners()));
    _engineer_txt.setString(std::to_string(_ship->countEngineers()));
    _weapon_txt.setString("Lvl " + std::to_string(_ship->getWeapon()->getLvl()));
    _shield_txt.setString("Lvl " + std::to_string(_ship->getShield()->getLvl()));
    _equipment_txt.setString("Lvl " + std::to_string(_ship->getEquipment()->getLvl()));
}

void Game::addButton(sf::Vector2f pos, std::string label, std::function<void()> on_click, std::string icon) {
    sf::Texture temp_tex;
    sf::Vector2f size(300,80);
    if (!icon.empty()) {
        temp_tex.loadFromFile("asset/sprites/ui/icons/" + icon);
        size = sf::Vector2f(temp_tex.getSize().x, temp_tex.getSize().y);
    }
    _buttons.emplace_back(pos, size, label, _font, on_click, icon);
}

void Game::updateTravelSelectScreen() {
    _buttons.clear();
    for (auto reg : _regions) {
        if (_ship->canUnlockRegion(reg)) {
            if (reg->isLocked()) reg->setLocked(false);
            for (auto pl : reg->getPlanets()) {
                if (pl != _ship->getCurrentPlanet()) {
                    addButton(sf::Vector2f(10, 10 + _buttons.size() * 90), pl->getName(), [this, pl, reg]() {
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
            showMessage("Region locked! Upgrade equipment.");
        }
    }
    
    addButton(sf::Vector2f(10, 10 + _buttons.size() * 90), "Back", [this]() {
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
    updateStatus();
}

void Game::checkWinCondition() {
    if (_ship->getCurrentPlanet()->getName() == "Tepler-A" &&
        _ship->getWeapon()->getLvl() >= 3 && _ship->getShield()->getLvl() >= 3 && _ship->getEquipment()->getLvl() >= 3) {
        _state = GameState::WIN;
    }
}

void Game::showMessage(std::string msg) {
    _message_log->addMessage(msg);
}
