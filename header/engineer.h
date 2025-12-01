#ifndef ENGINEER_H
#define ENGINEER_H

#include "crew.h"

class Engineer : public Crew {
private:
    int _price;
    int _work_rate;

public:
    Engineer(int id, int lvl, int price, int work_rate);
    int getPrice() const;
    int getWorkRate() const;
};

#endif
