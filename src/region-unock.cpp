#include "../header/region-unlock.h"
#include "../header/spaceship.h"
#include "../header/weapon.h"
#include "../header/shield.h"

RegionUnlockRequirement::RegionUnlockRequirement(int weapon_lvl, int shield_lvl)
    : _req_weapon_lvl(weapon_lvl), _req_shield_lvl(shield_lvl) {}

bool RegionUnlockRequirement::meetsReq(Spaceship* ship) const {
    return ship->getWeapon()->getLvl() >= _req_weapon_lvl &&
           ship->getShield()->getLvl() >= _req_shield_lvl;
}
