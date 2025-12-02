#ifndef WEAPON_H
#define WEAPON_H

class Weapon {
private:
    int _lvl;
    int _dmg;
    float _fire_rate; // New

public:
    Weapon(int lvl, int dmg);
    int getLvl() const;
    int getDmg() const;
    float getFireRate() const;
    void upgrade();
};

#endif
