#ifndef REGION_UNLOCK_H
#define REGION_UNLOCK_H
class Spaceship;
class RegionUnlockRequirement {
private:
    int _req_weapon_lvl;
    int _req_shield_lvl;
public:
    RegionUnlockRequirement(int weapon_lvl, int shield_lvl);
    bool meetsReq(Spaceship* ship) const;
};
#endif
