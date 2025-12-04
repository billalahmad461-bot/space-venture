#ifndef UPGRADE_STATION_H
#define UPGRADE_STATION_H
class Planet;
class Spaceship;
class UpgradeStation {
private:
    Planet* _h_planet;
public:
    UpgradeStation(Planet* planet);
    void upgradeWeapon(Spaceship* ship, int engineers);
    void upgradeShield(Spaceship* ship, int engineers);
    void upgradeEquipment(Spaceship* ship, int engineers);
    void upgradeMaxFuel(Spaceship* ship, int engineers);
};
#endif
