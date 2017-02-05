#pragma once
#include "Creature.hpp"
#include "StatusTypes.hpp"

class HungerCalculator
{
  public:
    int calculate_hunger_damage(CreaturePtr creature, const ulonglong num_ticks) const;
    int calculate_pct_chance_mark_health(const HungerLevel hl, const bool is_hungerless);
    int calculate_pct_chance_hunger_while_sated() const;

  protected:
    static const int HUNGER_DAMAGE_PER_TICK;
    static const int PCT_CHANCE_HUNGER_WHILE_SATED;
};

