#ifndef SHIELD_H
#define SHIELD_H
class Shield {
private:
    int _lvl;
    int _hp;
    int _current_hp;
public:
    Shield(int lvl, int hp);
    int getLvl() const;
    int getHp() const;
    int getCurrentHp() const;
    void setCurrentHp(int hp);
    void upgrade();
    void takeDamage(int dmg);
    void regen(int amt);
};
#endif
