#include "../header/spaceship.h"
#include <iostream>
#include <thread>
#include <chrono>

Spaceship::Spaceship(std::string name) : _name(name), _equipment_lvl(1), _fuel(100), _money(200) {
    _weapon = new Weapon(1, 10);
    _shield = new Shield(1, 100);
    loadSprites();
    _position = sf::Vector2f(400, 500);  // Default for minigame
}

Spaceship::~Spaceship() {
    delete _weapon;
    delete _shield;
    for (auto c : _crew) delete c;
    for (auto r : _cargo) delete r;
}

void Spaceship::travel(Region* d_region, Planet* d_planet) {
    if (d_region->isLocked()) return;
    // Animatic: sleep 5s
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // Chance encounter
    if (rand() % 100 < _region->getDangerLevel() * 10) {
        if (rand() % 2 == 0) encounterPirates(_region);
        else encounterAsteroids(_region);
    }
    _current_planet = d_planet;
    _region = d_region;
    _fuel -= 20;  // Consume fuel
}

void Spaceship::encounterPirates(Region* c_region) {
    // Trigger minigame with pirates
}

void Spaceship::encounterAsteroids(Region* c_region) {
    // Trigger minigame with asteroids
}

void Spaceship::collectResources(std::string resource, int miners) {
    if (miners <= 0) return;
    // Find resource on planet
    for (auto res : _current_planet->getResources()) {
        if (res->getType() == resource && (!res->isLocked() || _equipment_lvl >= res->getPrice() / 10)) {
            int time = 30 / miners;  // Seconds
            std::this_thread::sleep_for(std::chrono::seconds(time));
            int amount = miners * 5;  // Assume
            // Add to cargo
            bool found = false;
            for (auto c : _cargo) {
                if (c->getType() == resource) {
                    c->addAmount(amount);
                    found = true;
                    break;
                }
            }
            if (!found) _cargo.push_back(new Resource(resource, false, res->getPrice(), amount));
            break;
        }
    }
}

void Spaceship::manageResources() {
    // UI for sell
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

void Spaceship::update() {
    _position += _velocity;
    _sprite_top.setPosition(_position);
}

void Spaceship::shoot(std::vector<Bullet*>& bullets) {
    bullets.push_back(new Bullet(_position, sf::Vector2f(0, -10), _weapon->getDmg(), true));
}

void Spaceship::setRegion(Region* region) { _region = region; }

void Spaceship::setCurrentPlanet(Planet* planet) { _current_planet = planet; }

void Spaceship::setVelocity(sf::Vector2f velocity) { _velocity = velocity; }
