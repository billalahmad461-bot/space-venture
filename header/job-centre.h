#ifndef JOB_CENTRE_H
#define JOB_CENTRE_H

#include "planet.h"
#include "crew.h"
#include "spaceship.h"

class JobCentre {
private:
    Planet* _h_planet;

public:
    JobCentre(Planet* planet);
    void displayAvailable();  // UI
    void hireCrew(Crew* crew_member, Spaceship* ship);
    void upgradeCrew(char option, Spaceship* ship);
};

#endif
