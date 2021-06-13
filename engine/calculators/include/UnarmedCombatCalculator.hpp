#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"

class UnarmedCombatCalculator
{
  public:
    bool is_attack_unarmed(CreaturePtr creature, const AttackType attack_type) const;
    int calculate_pct_chance_free_kick(CreaturePtr creature) const;

  protected:
    static const int UNARMED_SKILL_KICK_SUBTRAHEND;
};

