#include "../header/miner.h"

Miner::Miner(int id, int lvl, int price, int mine_rate)
    : Crew(id, lvl, "miner"), _price(price), _mine_rate(mine_rate) {}

int Miner::getPrice() const { return _price; }

int Miner::getRate() const { return _mine_rate; }
