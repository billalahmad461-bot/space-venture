#include "../../header/stations/refuelling-station.h"
#include "../../header/world/planet.h"
#include "../../header/entities/spaceship.h"
RefuellingStation::RefuellingStation(Planet* planet) : _h_planet(planet) {}
void RefuellingStation::refuel(int amount, Spaceship* ship) {
    int cost = amount * FUEL_PRICE;
    if (ship->getMoney() >= cost) {
        ship->setFuel(ship->getFuel() + amount);
        ship->setMoney(ship->getMoney() - cost);
    }
}
void RefuellingStation::upgradeFuel(Spaceship* ship, int engineers) {
    if (engineers >= 2) {
        ship->upgradeMaxFuel();
    }
}
