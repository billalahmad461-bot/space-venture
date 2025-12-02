#ifndef REGION_H
#define REGION_H

#include <string>
#include <vector>
#include "threat.h"
#include "region-unlock.h"

class Planet;

class Region {
private:
    std::string _name;
    std::vector<Planet*> _planets;
    bool _lock;
    int _danger_level;
    RegionUnlockRequirement* _unlock_req;

public:
    Region(std::string name, bool lock, int danger_level, RegionUnlockRequirement* unlock_req);
    ~Region();
    void addPlanet(Planet* planet);
    std::vector<Planet*> getPlanets() const;
    bool isLocked() const;
    void setLocked(bool lock);
    int getDangerLevel() const;
    void generateSky();
    std::vector<Threat*> generateThreats();
    void unlock();
    std::string getName() const;
    RegionUnlockRequirement* getUnlockReq() const;
};

#endif
