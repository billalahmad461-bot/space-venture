#include "../header/spaceship.h"
#include <iostream>
#include <thread>
#include <chrono>

Spaceship::Spaceship(std::string name) : _name(name), _fuel(100), _max_fuel(100), _money(200) {
    _weapon = new Weapon(1, 10);
    _shield = new Shield(1, 100);
    _equipment = new Equipment(1);
    loadSprites();
    _position = sf::Vector2f(400, 500);
}

Spaceship::~Spaceship() {
    delete _weapon;
    delete _shield;
    delete _equipment;
    for (auto c : _crew) delete c;
    for (auto r : _cargo) delete r;
}

void Spaceship::travel(Region* d_region, Planet* d_planet) {
    if (d_region->isLocked()) return;
    int fuel_cost = (_region == d_region) ? 20 : 50;
    if (_fuel < fuel_cost) return;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    _current_planet = d_planet;
    _region = d_region;
    _fuel -= fuel_cost;
}

void Spaceship::encounterPirates(Region* c_region) {
    // Trigger minigame with pirates
}

void Spaceship::encounterAsteroids(Region* c_region) {
    // Trigger minigame with asteroids
}

void Spaceship::collectResources(std::string resource, int miners, int equipment_lvl) {
    if (miners <= 0) return;
    for (auto res : _current_planet->getResources()) {
        if (res->getType() == resource && equipment_lvl >= res->getReqEquipLvl()) {
            int amount = miners * equipment_lvl * 5;
            bool found = false;
            for (auto c : _cargo) {
                if (c->getType() == resource) {
                    c->addAmount(amount);
                    found = true;
                    break;
                }
            }
            if (!found) _cargo.push_back(new Resource(resource, res->getReqEquipLvl(), res->getPrice(), amount));
            break;
        }
    }
}

void Spaceship::manageResources() {
    // UI for sell
}

void Spaceship::sellResource(std::string type, int amount) {
    for (auto& c : _cargo) {
        if (c->getType() == type) {
            int sell_amt = (amount == 0 || amount > c->getAmount()) ? c->getAmount() : amount;
            c->addAmount(-sell_amt);
            _money += sell_amt * c->getPrice();
            if (c->getAmount() == 0) {
                // Optionally remove
            }
            break;
        }
    }
}

void Spaceship::addCrew(Crew* crew) {
    _crew.push_back(crew);
}

int Spaceship::countMiners() const {
    int count = 0;
    for (auto c : _crew) if (c->getType() == "miner") count++;
    return count;
}

int Spaceship::countEngineers() const {
    int count = 0;
    for (auto c : _crew) if (c->getType() == "engineer") count++;
    return count;
}

Weapon* Spaceship::getWeapon() const { return _weapon; }

Shield* Spaceship::getShield() const { return _shield; }

Equipment* Spaceship::getEquipment() const { return _equipment; }

Planet* Spaceship::getCurrentPlanet() const { return _current_planet; }

Region* Spaceship::getRegion() const { return _region; }

int Spaceship::getFuel() const { return _fuel; }

void Spaceship::setFuel(int fuel) {
    _fuel = std::min(fuel, _max_fuel);
}

int Spaceship::getMaxFuel() const { return _max_fuel; }

int Spaceship::getMoney() const { return _money; }

void Spaceship::setMoney(int money) { _money = money; }

std::vector<Resource*> Spaceship::getCargo() const { return _cargo; }

const std::vector<Crew*>& Spaceship::getCrew() const { return _crew; }

void Spaceship::loadSprites() {
    sf::Texture tex_top, tex_main;
    tex_top.loadFromFile("asset/sprites/spaceship-top.png");
    tex_main.loadFromFile("asset/sprites/spaceship-main.png");
    _sprite_top.setTexture(tex_top);
    _sprite_main.setTexture(tex_main);
}

const sf::Sprite& Spaceship::getSpriteTop() const { return _sprite_top; }

const sf::Sprite& Spaceship::getSpriteMain() const { return _sprite_main; }

sf::Vector2f Spaceship::getPosition() const { return _position; }

void Spaceship::setPosition(sf::Vector2f pos) { _position = pos; _sprite_top.setPosition(pos); }

void Spaceship::update(float delta) {
    _position += _velocity * delta;
    _sprite_top.setPosition(_position);
}

void Spaceship::shoot(std::vector<Bullet*>& bullets) {
    if (_shoot_clock.getElapsedTime().asSeconds() > 0.5f) {
        bullets.push_back(new Bullet(_position, sf::Vector2f(0, -300.f), _weapon->getDmg(), true));
        _shoot_clock.restart();
    }
}

void Spaceship::setRegion(Region* region) { _region = region; }

void Spaceship::setCurrentPlanet(Planet* planet) { _current_planet = planet; }

void Spaceship::setVelocity(sf::Vector2f velocity) { _velocity = velocity; }

bool Spaceship::consumeResource(std::string type, int amount) {
    for (auto& c : _cargo) {
        if (c->getType() == type && c->getAmount() >= amount) {
            c->addAmount(-amount);
            return true;
        }
    }
    return false;
}

bool Spaceship::canUnlockRegion(Region* region) {
    if (!region->isLocked()) return true;
    return region->getUnlockReq()->meetsReq(this);
}

void Spaceship::upgradeMaxFuel() {
    _max_fuel += 50;
}

void Spaceship::takeDamage(int dmg) {
    _shield->takeDamage(dmg);
    if (_shield->getCurrentHp() <= 0) {
        // Penalty: lose random resource or crew
    }
}

int Spaceship::getTotalMiningRate() const {
    int rate = 0;
    for (auto c : _crew) {
        if (c->getType() == "miner") rate += c->getRate();
    }
    return rate;
}

int Spaceship::getTotalEngineeringRate() const {
    int rate = 0;
    for (auto c : _crew) {
        if (c->getType() == "engineer") rate += c->getRate();
    }
    return rate;
}
