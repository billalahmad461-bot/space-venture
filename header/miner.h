#ifndef MINER_H
#define MINER_H

#include "crew.h"

class Miner : public Crew {
private:
    int _price;
    int _mine_rate;

public:
    Miner(int id, int lvl, int price, int mine_rate);
    int getPrice() const override;
    int getRate() const override;
};

#endif
