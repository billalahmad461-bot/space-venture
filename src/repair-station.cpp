#include "../header/repair-station.h"
#include "../header/planet.h"
#include "../header/spaceship.h"
#include "../header/shield.h"

RepairStation::RepairStation(Planet* planet) : _h_planet(planet) {}

void RepairStation::repairSpaceship(Spaceship* ship, int engineers) {
    ship->getShield()->setCurrentHp(ship->getShield()->getHp());
}
