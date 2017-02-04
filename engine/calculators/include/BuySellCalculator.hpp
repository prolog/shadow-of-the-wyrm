#pragma once
#include "Creature.hpp"

class BuySellCalculator
{
  public:
    // Get the base sale price (before any premiums, etc)
    int get_sale_price(ItemPtr item);

    int calc_pct_chance_bargain(CreaturePtr creature);
    int calc_pct_discount_buy(CreaturePtr creature);
    int calc_pct_premium_sell(CreaturePtr creature);

  protected:
    int get_prem_disc_percentage(CreaturePtr creature);

    static const int PREMIUM_DISCOUNT_DIVISOR;
    static const int SALE_DIVISOR;
};

