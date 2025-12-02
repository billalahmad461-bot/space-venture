#include "../header/spaceship.h"
#include <iostream>
#include <sstream>

Spaceship::Spaceship(std::string name) : _name(name), _equipment_lvl(1), _fuel(100), _money(200) {
    _weapon = new Weapon(1, 10);
    _shield = new Shield(1, 100);
    loadSprites();
    _position = sf::Vector2f(400, 500);
}

Spaceship::~Spaceship() {
    delete _weapon;
    delete _shield;
    for (auto c : _crew) delete c;
    for (auto r : _cargo) delete r;
}

void Spaceship::travel(Region* d_region, Planet* d_planet) {
    if (d_region->isLocked()) return;
    _current_planet = d_planet;
    _region = d_region;
    _fuel -= 20;
}

void Spaceship::encounterPirates(Region* c_region) {
}

void Spaceship::encounterAsteroids(Region* c_region) {
}

void Spaceship::collectResources(std::string resource, int miners, int equipment_lvl) {
    if (miners <= 0) return;
    bool found_res = false;
    for (auto res : _current_planet->getResources()) {
        if (res->getType() == resource && (!res->isLocked() || equipment_lvl >= res->getPrice() / 10)) {
            found_res = true;
            int amount = miners * 5;
            bool found_cargo = false;
            for (auto c : _cargo) {
                if (c->getType() == resource) {
                    c->addAmount(amount);
                    found_cargo = true;
                    break;
                }
            }
            if (!found_cargo) _cargo.push_back(new Resource(resource, false, res->getPrice(), amount));
            break;
        }
    }
}

void Spaceship::manageResources() {
}

void Spaceship::sellResource(std::string type, int amount) {
    for (auto& c : _cargo) {
        if (c->getType() == type && c->getAmount() >= amount) {
            c->addAmount(-amount);
            _money += amount * c->getPrice();
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

int Spaceship::getEquipmentLvl() const { return _equipment_lvl; }

void Spaceship::setEquipmentLvl(int lvl) { _equipment_lvl = lvl; }

Planet* Spaceship::getCurrentPlanet() const { return _current_planet; }

Region* Spaceship::getRegion() const { return _region; }

int Spaceship::getFuel() const { return _fuel; }

void Spaceship::setFuel(int fuel) { _fuel = fuel; }

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
    bullets.push_back(new Bullet(_position, sf::Vector2f(0, -300.f), _weapon->getDmg(), true));
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
