#include "../header/region.h"
#include "../header/pirate.h"
#include "../header/asteroid.h"
#include "../header/planet.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

Region::Region(std::string name, bool lock, int danger_level, RegionUnlockRequirement* unlock_req)
    : _name(name), _lock(lock), _danger_level(danger_level), _unlock_req(unlock_req) {}

Region::~Region() {
    for (auto p : _planets) delete p;
    delete _unlock_req;
}

void Region::addPlanet(Planet* planet) {
    _planets.push_back(planet);
}

std::vector<Planet*> Region::getPlanets() const { return _planets; }

bool Region::isLocked() const { return _lock; }

void Region::setLocked(bool lock) { _lock = lock; }

int Region::getDangerLevel() const { return _danger_level; }

void Region::generateSky() {
}

std::vector<Threat*> Region::generateThreats() {
    std::vector<Threat*> threats;
    int num = _danger_level * 2 + (rand() % _danger_level);
    for (int i = 0; i < num; ++i) {
        sf::Vector2f pos(static_cast<float>(rand() % 800), static_cast<float>(rand() % 100));
        if (rand() % 2 == 0) {
            threats.push_back(new Pirate(_danger_level, pos));
        } else {
            threats.push_back(new Asteroid(_danger_level, pos));
        }
    }
    return threats;
}

void Region::unlock() { _lock = false; }

std::string Region::getName() const { return _name; }

RegionUnlockRequirement* Region::getUnlockReq() const { return _unlock_req; }
