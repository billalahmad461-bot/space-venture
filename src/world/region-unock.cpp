#include "../../header/world/region-unlock.h"
#include "../../header/entities/spaceship.h"
#include "../../header/entities/weapon.h"
#include "../../header/entities/shield.h"
RegionUnlockRequirement::RegionUnlockRequirement(int weapon_lvl, int shield_lvl)
    : _req_weapon_lvl(weapon_lvl), _req_shield_lvl(shield_lvl) {}
bool RegionUnlockRequirement::meetsReq(Spaceship* ship) const {
    return ship->getWeapon()->getLvl() >= _req_weapon_lvl &&
           ship->getShield()->getLvl() >= _req_shield_lvl;
}
