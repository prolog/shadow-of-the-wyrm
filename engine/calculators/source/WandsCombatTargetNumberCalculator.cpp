#include "WandsCombatTargetNumberCalculator.hpp"

WandsCombatTargetNumberCalculator::WandsCombatTargetNumberCalculator()
: MagicalCombatTargetNumberCalculator(AttackType::ATTACK_TYPE_MAGICAL_WANDS)
{
}

SkillType WandsCombatTargetNumberCalculator::get_attacker_skill() const
{
  return SkillType::SKILL_GENERAL_WANDCRAFT;
}

#ifdef UNIT_TESTS
#include "unit_tests/WandsCombatTargetNumberCalculator_test.cpp"
#endif
