#include "../header/repair-station.h"

RepairStation::RepairStation(Planet* planet) : _h_planet(planet) {}

void RepairStation::repairSpaceship(Spaceship* ship, int engineers) {
    ship->getShield()->setCurrentHp(ship->getShield()->getHp());
}
