#include "../../header/stations/repair-station.h"
#include "../../header/world/planet.h"
#include "../../header/entities/spaceship.h"
#include "../../header/entities/shield.h"
RepairStation::RepairStation(Planet* planet) : _h_planet(planet) {}
void RepairStation::repairSpaceship(Spaceship* ship, int engineers) {
    ship->getShield()->setCurrentHp(ship->getShield()->getHp());
}
