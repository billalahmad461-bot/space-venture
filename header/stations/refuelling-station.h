#ifndef REFUELLING_STATION_H
#define REFUELLING_STATION_H
class Planet;
class Spaceship;
class RefuellingStation {
private:
    Planet* _h_planet;
    const int FUEL_PRICE = 1;
public:
    RefuellingStation(Planet* planet);
    void refuel(int amount, Spaceship* ship);
    void upgradeFuel(Spaceship* ship, int engineers);
};
#endif
