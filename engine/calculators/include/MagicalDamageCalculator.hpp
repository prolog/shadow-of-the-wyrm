#pragma once
#include "DamageCalculator.hpp"

class MagicalDamageCalculator : public DamageCalculator
{
  public:
    MagicalDamageCalculator(const PhaseOfMoonType new_pom);
    
    virtual int calculate(CreaturePtr defending_creature, const bool sneak_attack, const bool slays_creatures_race, const Damage& damage, const int base_damage, const float soak_multiplier) override;
    virtual Damage calculate_base_damage_object(CreaturePtr creature) override;
    virtual Damage calculate_base_damage_with_bonuses_or_penalties(CreaturePtr creature) override;

  protected:
    int get_skill_modifier(CreaturePtr creature, const SkillType magic_category);
    int get_stat_modifier(CreaturePtr creature);

    static const int MAGICAL_DAMAGE_SKILL_DIVISOR;
    static const int MAGICAL_DAMAGE_STAT_DIVISOR;
};
