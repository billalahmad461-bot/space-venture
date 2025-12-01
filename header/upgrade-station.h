#ifndef UPGRADE_STATION_H
#define UPGRADE_STATION_H

#include "planet.h"
#include "spaceship.h"

class UpgradeStation {
private:
    Planet* _h_planet;

public:
    UpgradeStation(Planet* planet);
    void upgradeWeapon(Spaceship* ship, int engineers);
    void upgradeShield(Spaceship* ship, int engineers);
    void upgradeEquipment(Spaceship* ship, int engineers);
};

#endif
