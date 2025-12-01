#ifndef REPAIR_STATION_H
#define REPAIR_STATION_H

#include "planet.h"
#include "spaceship.h"

class RepairStation {
private:
    Planet* _h_planet;

public:
    RepairStation(Planet* planet);
    void repairSpaceship(Spaceship* ship, int engineers);
};

#endif
