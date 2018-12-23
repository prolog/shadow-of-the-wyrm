#include "PapercraftCalculator.hpp"

const int PapercraftCalculator::BASE_PCT_CHANCE_SUCCESS = 50;
const int PapercraftCalculator::PAPERCRAFT_SKILL_DIVISOR = 2;

int PapercraftCalculator::calculate_pct_chance_success(CreaturePtr creature)
{
  int pct_chance = 0;

  if (creature != nullptr)
  {
    int papercraft_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_PAPERCRAFT);

    pct_chance = BASE_PCT_CHANCE_SUCCESS + (papercraft_val / PAPERCRAFT_SKILL_DIVISOR);
  }

  return pct_chance;
}
