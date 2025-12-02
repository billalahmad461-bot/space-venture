#ifndef JOB_CENTRE_H
#define JOB_CENTRE_H

#include <vector>
class Planet;
class Crew;
class Spaceship;

class JobCentre {
private:
    Planet* _h_planet;

public:
    JobCentre(Planet* planet);
    void displayAvailable();
    void hireCrew(Crew* crew_member, Spaceship* ship);
    void upgradeCrew(int crew_id, Spaceship* ship);
    std::vector<Crew*> getAvailableHires() const;
    void displayCrewForUpgrade(Spaceship* ship);
};

#endif
