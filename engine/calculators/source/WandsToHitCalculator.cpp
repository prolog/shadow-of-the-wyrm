#include "WandsToHitCalculator.hpp"
#include "SkillManager.hpp"

WandsToHitCalculator::WandsToHitCalculator()
: ToHitCalculator(AttackType::ATTACK_TYPE_MAGICAL_WANDS)
{
}

int WandsToHitCalculator::calculate(CreaturePtr creature)
{
  int to_hit = 0;

  if (creature)
  {
    to_hit = creature->get_to_hit().get_current();
    SkillManager sm;

    // Have you ever tried directing a fireball while drunk?
    // It's not easy!
    int bac_modifier = static_cast<int>(creature->get_blood().get_blood_alcohol_content() * 100);
    int level_bonus  = get_level_bonus(creature);
    int wc_bonus     = sm.get_skill_value(creature, SkillType::SKILL_GENERAL_WANDCRAFT) / NWP_SKILL_BONUS_DIVISOR;
    int charisma     = get_statistic(creature).get_current();
    int modifiers    = get_modifier_bonus(creature);

    to_hit += level_bonus;
    to_hit += wc_bonus;
    to_hit += (charisma - 10) / 3;
    to_hit += modifiers;
    to_hit -= bac_modifier;
  }

  return to_hit;
}

Statistic& WandsToHitCalculator::get_statistic(CreaturePtr creature)
{
  return creature->get_charisma_ref();
}

#ifdef UNIT_TESTS
#include "unit_tests/WandsToHitCalculator_test.cpp"
#endif
