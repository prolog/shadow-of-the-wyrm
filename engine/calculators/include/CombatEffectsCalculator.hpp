#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"

class CombatEffectsCalculator
{
  public:
    int calc_pct_chance_counter_strike(CreaturePtr creature) const;
    int calculate_knock_back_pct_chance(const AttackType attack_type, CreaturePtr attacking_creature, CreaturePtr attacked_creature);

  protected:
    static const int COMBAT_SKILL_DIVISOR;
    static const int DEXTERITY_DIVISOR;
};

