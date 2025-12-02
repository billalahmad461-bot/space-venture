#ifndef JOB_CENTRE_H
#define JOB_CENTRE_H

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
    void upgradeCrew(char option, Spaceship* ship);
};

#endif
