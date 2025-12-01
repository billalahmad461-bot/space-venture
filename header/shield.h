#ifndef SHIELD_H
#define SHIELD_H

class Shield {
private:
    int _lvl;
    int _hp;
    int _current_hp;  // Added missing attribute for current health

public:
    Shield(int lvl, int hp);
    int getLvl() const;
    int getHp() const;
    int getCurrentHp() const;
    void setCurrentHp(int hp);
    void upgrade();
    void takeDamage(int dmg);
};

#endif
