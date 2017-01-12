#pragma once
#include "Creature.hpp"
#include "Race.hpp"

class CreatureSplitCalculator
{
  public:
    // Can the creature's race split?  Can the creature itself do so in 
    // its present state?  What's the chance, based on the creature's
    // danger level?  Are there adjacent tiles free?
    int calculate_pct_chance_split(CreaturePtr creature, RacePtr race, MapPtr current_map);
    
    // How many HP should the new creature have?  AP remains the same.
    int calculate_split_hit_points(CreaturePtr creature);

  protected:
    static const int BASE_MIN_CHANCE_SPLIT;
    static const int HP_SPLIT_DIVISOR;
};

