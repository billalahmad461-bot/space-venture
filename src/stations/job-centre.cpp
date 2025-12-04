#include "../../header/stations/job-centre.h"
#include "../../header/world/planet.h"
#include "../../header/crew/crew.h"
#include "../../header/entities/spaceship.h"
#include "../../header/crew/miner.h"
#include "../../header/crew/engineer.h"
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
void JobCentre::upgradeCrew(int crew_id, Spaceship* ship) {
    for (auto c : ship->getCrew()) {
        if (c->getId() == crew_id) {
            int cost = c->getUpgradeCost();
            if (ship->getMoney() >= cost) {
                c->upgrade();
                if (c->getType() == "miner") {
                    Miner* m = dynamic_cast<Miner*>(c);
                    m->setMineRate(m->getRate() / c->getLvl() + 2);
                } else if (c->getType() == "engineer") {
                    Engineer* e = dynamic_cast<Engineer*>(c);
                    e->setWorkRate(e->getRate() / c->getLvl() + 2);
                }
                ship->setMoney(ship->getMoney() - cost);
            }
            break;
        }
    }
}
std::vector<Crew*> JobCentre::getAvailableHires() const {
    std::vector<Crew*> hires;
    hires.push_back(new Miner(0, 1, 50, 5));
    hires.push_back(new Engineer(0, 1, 50, 5));
    return hires;
}
void JobCentre::displayCrewForUpgrade(Spaceship* ship) {
}
