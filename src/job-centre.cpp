#include "../header/job-centre.h"
#include <iostream>

JobCentre::JobCentre(Planet* planet) : _h_planet(planet) {}

void JobCentre::displayAvailable() {
}

void JobCentre::hireCrew(Crew* crew_member, Spaceship* ship) {
    int price = crew_member->getPrice();
    if (ship->getMoney() >= price) {
        ship->addCrew(crew_member);
        ship->setMoney(ship->getMoney() - price);
    } else {
        delete crew_member;
    }
}

void JobCentre::upgradeCrew(char option, Spaceship* ship) {
}
