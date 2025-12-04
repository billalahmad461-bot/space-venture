#ifndef REPAIR_STATION_H
#define REPAIR_STATION_H
class Planet;
class Spaceship;
class RepairStation {
private:
    Planet* _h_planet;
public:
    RepairStation(Planet* planet);
    void repairSpaceship(Spaceship* ship, int engineers);
};
#endif
