#include "../header/job-centre.h"
#include "../header/miner.h"
#include "../header/engineer.h"
#include <iostream>

JobCentre::JobCentre(Planet* planet) : _h_planet(planet) {}

void JobCentre::displayAvailable() {
    // UI in game
}

void JobCentre::hireCrew(Crew* crew_member, Spaceship* ship) {
    int price = dynamic_cast<Miner*>(crew_member) ? dynamic_cast<Miner*>(crew_member)->getPrice() : dynamic_cast<Engineer*>(crew_member)->getPrice();
    if (ship->getMoney() >= price) {
        ship->addCrew(crew_member);
        ship->setMoney(ship->getMoney() - price);
    }
}

void JobCentre::upgradeCrew(char option, Spaceship* ship) {
    // Assume option selects crew, upgrade lvl, pay money
}
