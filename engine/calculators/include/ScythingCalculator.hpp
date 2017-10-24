#pragma once
#include "Creature.hpp"

class ScythingCalculator
{
  public:
    int calc_pct_chance_scything_continues(CreaturePtr creature, const SkillType st, const int total_attacks);

  protected:
    static const int SCYTHING_ATTACK_MULTIPLIER;
};

