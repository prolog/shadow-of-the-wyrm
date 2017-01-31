#pragma once
#include "Creature.hpp"

class BuySellCalculator
{
  public:
    int calc_pct_chance_bargain(CreaturePtr creature);
    int calc_pct_discount_buy(CreaturePtr creature);
    int calc_pct_premium_sell(CreaturePtr creature);

  protected:
    int get_prem_disc_percentage(CreaturePtr creature);

    static const int PREMIUM_DISCOUNT_DIVISOR;
};

