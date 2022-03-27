#include "DivineCompanionCalculator.hpp"

const double DivineCompanionCalculator::BASE_HP_MULT = 1.3;
const double DivineCompanionCalculator::BASE_AP_MULT = 1.3;
const int DivineCompanionCalculator::DAMAGE_MODIFIER_LEVEL_DIVISOR = 2;

DivineCompanionCalculator::DivineCompanionCalculator(CreaturePtr new_leader)
: leader(new_leader)
{
}

Statistic DivineCompanionCalculator::calculate_hp(const Statistic& base_hp) const
{
  Statistic calc_hp = base_hp;
  int base_amount = static_cast<int>(calc_hp.get_base() * BASE_HP_MULT);
  int bonus = 0;

  if (leader != nullptr)
  {
    bonus = leader->get_skills().get_value(SkillType::SKILL_GENERAL_RELIGION);
  }

  calc_hp.set_base_current(base_amount + bonus);

  return calc_hp;
}

Statistic DivineCompanionCalculator::calculate_ap(const Statistic& base_ap) const
{
  Statistic calc_ap = base_ap;
  int base_amount = static_cast<int>(calc_ap.get_base() * BASE_AP_MULT);
  int bonus = 0;

  if (leader != nullptr)
  {
    bonus = leader->get_skills().get_value(SkillType::SKILL_GENERAL_RELIGION);
  }

  calc_ap.set_base_current(base_amount + bonus);

  return calc_ap;
}

int DivineCompanionCalculator::calculate_damage_modifier(CreaturePtr creature, const Damage& d) const
{
  int mod = 0;
  
  if (creature != nullptr)
  {
    mod = d.get_modifier() + (creature->get_level().get_current() / DAMAGE_MODIFIER_LEVEL_DIVISOR);
  }

  if (leader != nullptr)
  {
    mod += leader->get_skills().get_value(SkillType::SKILL_GENERAL_RELIGION);
  }

  return mod;
}

#ifdef UNIT_TESTS
#include "unit_tests/DivineCompanionCalculator_test.cpp"
#endif
