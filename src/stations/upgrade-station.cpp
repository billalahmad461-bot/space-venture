#include "../../header/stations/upgrade-station.h"
#include "../../header/world/planet.h"
#include "../../header/entities/spaceship.h"
#include "../../header/entities/weapon.h"
#include "../../header/entities/equipment.h"
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
