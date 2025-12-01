#ifndef WEAPON_H
#define WEAPON_H

class Weapon {
private:
    int _lvl;
    int _dmg;

public:
    Weapon(int lvl, int dmg);
    int getLvl() const;
    int getDmg() const;
    void upgrade();
};

#endif
