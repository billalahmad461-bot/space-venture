#include "../header/region.h"
#include "../header/pirate.h"
#include "../header/asteroid.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

Region::Region(std::string name, bool lock, int danger_level)
    : _name(name), _lock(lock), _danger_level(danger_level) {}

Region::~Region() {
    for (auto p : _planets) delete p;
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
    int num = _danger_level + (rand() % 3);
    bool is_pirate = rand() % 2 == 0;
    for (int i = 0; i < num; ++i) {
        sf::Vector2f pos(static_cast<float>(rand() % 800), static_cast<float>(rand() % 100));
        if (is_pirate) {
            threats.push_back(new Pirate(_danger_level, pos));
        } else {
            threats.push_back(new Asteroid(_danger_level, pos));
        }
    }
    return threats;
}
