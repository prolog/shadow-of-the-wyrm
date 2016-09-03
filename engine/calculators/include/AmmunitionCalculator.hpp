#pragma once
#include "Creature.hpp"
#include "Item.hpp"

class AmmunitionCalculator
{
  public:
    // Does the ammunition survive after use?
    bool survives(CreaturePtr creature, ItemPtr ammunition);

    std::pair<int, int> calculate_stack_size(ItemPtr ammunition);
    
  protected:
    static const int BASE_PCT_CHANCE_BREAKAGE;
    static const int BASE_PCT_CHANCE_SURVIVAL;
    static const int ARCHERY_SKILL_SURVIVAL_DIVISOR;
    static const int ITEM_WEIGHT_SURVIVAL_DIVISOR;

    static const std::map<Weight, std::pair<int, int>> AMMUNITION_STACK_RANGES;
};
