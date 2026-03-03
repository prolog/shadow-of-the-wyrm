#pragma once
#include "Creature.hpp"
#include "EngineConversion.hpp"

class StealthCalculator
{
  public:
    int calculate_pct_chance_sneak_attack(CreaturePtr attacking_creature, CreaturePtr attacked_creature) const;

  protected:
    int get_burden_penalty(const BurdenLevel bl) const;
};

