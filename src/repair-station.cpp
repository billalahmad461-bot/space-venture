#include "../header/repair-station.h"

RepairStation::RepairStation(Planet* planet) : _h_planet(planet) {}

void RepairStation::repairSpaceship(Spaceship* ship, int engineers) {
    // Time = (max - current) / engineers, assume instant
    ship->getShield()->setCurrentHp(ship->getShield()->getHp());
}
