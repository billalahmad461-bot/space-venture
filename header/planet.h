#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <vector>
#include "region.h"
#include "resource.h"
#include "repair-station.h"
#include "upgrade-station.h"
#include "refuelling-station.h"
#include "job-centre.h"
#include "spaceship.h"
#include <SFML/Graphics.hpp>

class Planet {
private:
    std::string _name;
    Region* _region;
    std::vector<Resource*> _resources;
    RepairStation* _repair_station;
    UpgradeStation* _upgrade_station;
    RefuellingStation* _refuelling_station;
    JobCentre* _job_centre;
    sf::Sprite _sprite;
    int _req_upgrade_lvl;

public:
    Planet(std::string name, Region* region, int req_upgrade_lvl = 1);
    ~Planet();
    void displayOptions();
    void refuel(int f, Spaceship* ship);
    void repairShip(Spaceship* ship, int engineers);
    void upgradeShip(Spaceship* ship, int engineers);
    void manageCrew(Spaceship* ship);
    std::string getName() const;
    const std::vector<Resource*>& getResources() const;
    void addResource(Resource* resource);
    JobCentre* getJobCentre() const;
    UpgradeStation* getUpgradeStation() const;
    RefuellingStation* getRefuellingStation() const;
    RepairStation* getRepairStation() const;
    void loadSprite(const std::string& filename);
    const sf::Sprite& getSprite() const;
    bool hasStation(std::string type) const;
    Resource* getUniqueResource() const;
    Region* getRegion() const;
};

#endif
