#ifndef REGION_H
#define REGION_H

#include <string>
#include <vector>

class Planet;  // Forward declaration to break circular include

class Region {
private:
    std::string _name;
    std::vector<Planet*> _planets;
    bool _lock;
    int _danger_level;

public:
    Region(std::string name, bool lock, int danger_level);
    ~Region();
    void addPlanet(Planet* planet);
    std::vector<Planet*> getPlanets() const;
    bool isLocked() const;
    void setLocked(bool lock);
    int getDangerLevel() const;
    void generateSky();
    std::vector<Threat*> generateThreats();
};

#endif
