#include "ReadCalculator.hpp"

const int ReadCalculator::BASE_READING_ACV = 20;

ActionCostValue ReadCalculator::calculate_reading_acv(CreaturePtr creature)
{
  ActionCostValue calc_acv = BASE_READING_ACV;

  if (creature != nullptr)
  {
    int literacy = creature->get_skills().get_value(SkillType::SKILL_GENERAL_LITERACY);

    // - 1 to the acv for every 5 pts of Literacy
    calc_acv -= (literacy / 5);
  }

  return std::max(1, calc_acv);
}

