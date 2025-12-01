#include "../header/upgrade-station.h"

UpgradeStation::UpgradeStation(Planet* planet) : _h_planet(planet) {}

void UpgradeStation::upgradeWeapon(Spaceship* ship, int engineers) {
    // Time = 10 / engineers, assume instant for first
    ship->getWeapon()->upgrade();
}

void UpgradeStation::upgradeShield(Spaceship* ship, int engineers) {
    ship->getShield()->upgrade();
}

void UpgradeStation::upgradeEquipment(Spaceship* ship, int engineers) {
    ship->setEquipmentLvl(ship->getEquipmentLvl() + 1);
}
