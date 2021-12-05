#include "StatusEffectCalculator.hpp"

const int StatusEffectCalculator::MEDICINE_SUBTRAHEND = 5;

// The chance of the effect is the chance of the effect for the
// implementing class, plus the effect bonus.
int StatusEffectCalculator::pct_chance_effect(CreaturePtr creature, const int effect_bonus) const
{
  return calculate_pct_chance_effect(creature) + effect_bonus;
}

// Medicine gives you a very good chance to avoid status effects.
int StatusEffectCalculator::pct_chance_counteract_negative(CreaturePtr creature) const
{
  int pct_chance = 0;

  if (creature != nullptr)
  {
    int medicine_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_MEDICINE);
    pct_chance = std::max<int>(0, medicine_val - MEDICINE_SUBTRAHEND);
  }

  return pct_chance;
}