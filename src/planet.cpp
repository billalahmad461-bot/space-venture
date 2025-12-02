#include "../header/planet.h"
#include <iostream>

Planet::Planet(std::string name, Region* region)
    : _name(name), _region(region) {
    _repair_station = new RepairStation(this);
    _upgrade_station = new UpgradeStation(this);
    _refuelling_station = new RefuellingStation(this);
    _job_centre = new JobCentre(this);
}

Planet::~Planet() {
    delete _repair_station;
    delete _upgrade_station;
    delete _refuelling_station;
    delete _job_centre;
    for (auto res : _resources) delete res;
}

void Planet::displayOptions() {
}

void Planet::refuel(int f, Spaceship* ship) {
    _refuelling_station->refuel(f, ship);
}

void Planet::repairShip(Spaceship* ship, int engineers) {
    _repair_station->repairSpaceship(ship, engineers);
}

void Planet::upgradeShip(Spaceship* ship, int engineers) {
    _upgrade_station->upgradeWeapon(ship, engineers);
}

void Planet::manageCrew(Spaceship* ship) {
    _job_centre->displayAvailable();
}

std::string Planet::getName() const { return _name; }

const std::vector<Resource*>& Planet::getResources() const { return _resources; }

void Planet::addResource(Resource* resource) { _resources.push_back(resource); }

JobCentre* Planet::getJobCentre() const { return _job_centre; }

UpgradeStation* Planet::getUpgradeStation() const { return _upgrade_station; }

RefuellingStation* Planet::getRefuellingStation() const { return _refuelling_station; }

RepairStation* Planet::getRepairStation() const { return _repair_station; }

void Planet::loadSprite(const std::string& filename) {
    sf::Texture texture;
    texture.loadFromFile(filename);
    _sprite.setTexture(texture);
}

const sf::Sprite& Planet::getSprite() const { return _sprite; }
