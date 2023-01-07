#pragma once
#include "CombatTargetNumberCalculator.hpp"

class MagicalCombatTargetNumberCalculator : public CombatTargetNumberCalculator
{
  public:
    MagicalCombatTargetNumberCalculator();
    MagicalCombatTargetNumberCalculator(const AttackType attack_type);

    virtual int calculate(CreaturePtr attacking_creature, CreaturePtr attacked_creature) override;
    virtual int calculate_pct_chance_pass_through_untargetted_square(CreaturePtr attacking_creature, CreaturePtr creature_in_tile) override;

  protected:
    virtual SkillType get_attacker_skill() const;
};
