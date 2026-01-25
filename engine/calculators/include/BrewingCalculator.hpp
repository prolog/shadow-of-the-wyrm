#pragma once
#include "Creature.hpp"
#include "ItemTypes.hpp"

class BrewingCalculator
{
  public:
    int calc_pct_chance_additional_potion(CreaturePtr brewing_creature) const;
    std::map<ItemStatus, int> calc_item_status_pct_chance(CreaturePtr brewing_creature) const;


  protected:
    static const int ADDITIONAL_POTION_BREWING_DIVISOR;
    static const int STATUS_THRESHOLD_CURSED;
    static const int STATUS_THRESHOLD_UNCURSED;
    static const int STATUS_THRESHOLD_BLESSED;
};

