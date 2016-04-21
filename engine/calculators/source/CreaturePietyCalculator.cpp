#include "CreaturePietyCalculator.hpp"

// If a creature has 100 Religion, they would get a multiplier/divisor of
// 3.  etc.
float CreaturePietyCalculator::calculate_piety_multiplier(CreaturePtr creature)
{
  float mult = 1.0f;

  if (creature != nullptr)
  {
    mult = mult + static_cast<float>(creature->get_skills().get_value(SkillType::SKILL_GENERAL_RELIGION) * 0.02);
  }

  return mult;
}
