#ifndef EQUIPMENT_H
#define EQUIPMENT_H
class Equipment {
private:
    int _lvl;
    int _max_capacity;
public:
    Equipment(int lvl = 1, int max_capacity = 100);
    void upgrade();
    int getLvl() const;
};
#endif
