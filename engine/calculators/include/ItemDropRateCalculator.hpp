#pragma once
#include "Creature.hpp"

class ItemDropRateCalculator
{
  public:
    int calculate_pct_chance_item_drop(CreaturePtr creature);
    int calculate_pct_chance_currency_drop(CreaturePtr creature);
};

