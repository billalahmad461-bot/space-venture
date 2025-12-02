#include "../header/upgrade-station.h"
#include "../header/planet.h"
#include "../header/spaceship.h"
#include "../header/weapon.h"
#include "../header/equipment.h"

UpgradeStation::UpgradeStation(Planet* planet) : _h_planet(planet) {}

void UpgradeStation::upgradeWeapon(Spaceship* ship, int engineers) {
    if (engineers > 0) ship->getWeapon()->upgrade();
}

void UpgradeStation::upgradeShield(Spaceship* ship, int engineers) {
    if (engineers > 0) ship->getShield()->upgrade();
}

void UpgradeStation::upgradeEquipment(Spaceship* ship, int engineers) {
    if (engineers > 0) ship->getEquipment()->upgrade();
}

void UpgradeStation::upgradeMaxFuel(Spaceship* ship, int engineers) {
    if (engineers > 0) ship->upgradeMaxFuel();
}
