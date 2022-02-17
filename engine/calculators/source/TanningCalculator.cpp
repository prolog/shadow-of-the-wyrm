#include "TanningCalculator.hpp"
#include "RNG.hpp"

using namespace std;

const int TanningCalculator::COMBAT_MIN_DIVISOR = 50;
const int TanningCalculator::COMBAT_MAX_DIVISOR = 5;
const int TanningCalculator::EVADE_MIN_DIVISOR = 50;
const int TanningCalculator::EVADE_MAX_DIVISOR = 10;
const int TanningCalculator::SOAK_MIN_DIVISOR = 50;
const int TanningCalculator::SOAK_MAX_DIVISOR = 20;
const int TanningCalculator::BASE_IMPROVEMENT_PCT = 10;
const int TanningCalculator::MAX_IMPROVEMENT_PCT = 100;
const int TanningCalculator::BASE_RESIST_DIVISOR = 5;
const vector<pair<int, double>> TanningCalculator::SKILL_VALUE_DIVISORS = {{100, 2.5}, {75, 3}, {50, 3.5}, {25, 4}, {0, 5.0}};
const int TanningCalculator::PCT_CHANCE_EXTRA_POINT = 60;
const int TanningCalculator::VALUE_BONUS_MULTIPLIER = 3;

int TanningCalculator::calculate_value_bonus(const int bonus)
{
  if (bonus > 0)
  {
    return bonus * VALUE_BONUS_MULTIPLIER;
  }

  return 0;
}

int TanningCalculator::calculate_combat_bonus_min(CreaturePtr creature)
{
  int combat_bonus = 0;

  if (creature != nullptr)
  {
    combat_bonus = calculate_skills_bonus(creature, COMBAT_MIN_DIVISOR);
  }

  return combat_bonus;
}

int TanningCalculator::calculate_combat_bonus_max(CreaturePtr creature)
{
  int combat_bonus = 0;

  if (creature != nullptr)
  {
    combat_bonus = calculate_skills_bonus(creature, COMBAT_MAX_DIVISOR);
  }

  return combat_bonus;
}

int TanningCalculator::calculate_evade_bonus_min(CreaturePtr creature)
{
  int evade_bonus = 0;

  if (creature != nullptr)
  {
    evade_bonus = calculate_skills_bonus(creature, EVADE_MIN_DIVISOR);
  }

  return evade_bonus;
}

int TanningCalculator::calculate_evade_bonus_max(CreaturePtr creature)
{
  int evade_bonus = 0;

  if (creature != nullptr)
  {
    evade_bonus = calculate_skills_bonus(creature, EVADE_MAX_DIVISOR);
  }

  return evade_bonus;
}

int TanningCalculator::calculate_soak_bonus_min(CreaturePtr creature)
{
  int soak_bonus = 0;

  if (creature != nullptr)
  {
    soak_bonus = calculate_skills_bonus(creature, SOAK_MIN_DIVISOR);
  }

  return soak_bonus;
}

int TanningCalculator::calculate_soak_bonus_max(CreaturePtr creature)
{
  int soak_bonus = 0;

  if (creature != nullptr)
  {
    soak_bonus = calculate_skills_bonus(creature, SOAK_MAX_DIVISOR);
  }

  return soak_bonus;
}



int TanningCalculator::calculate_skills_bonus(CreaturePtr creature, const int divisor)
{
  int skill_bonus = 0;

  if (creature != nullptr)
  {
    vector<SkillType> check_skills = { SkillType::SKILL_GENERAL_CRAFTING, SkillType::SKILL_GENERAL_TANNING };
    Skills& skills = creature->get_skills();

    for (const auto& c_skill : check_skills)
    {
      skill_bonus += (skills.get_value(c_skill) / divisor);
    }
  }

  return skill_bonus;
}

// Calculate the resistances for a tanned item.  This will be based on the
// resistances of the skin itself, as well as on certain skills of the
// tanning creature.
Resistances TanningCalculator::calculate_item_resistances(CreaturePtr creature, const Resistances& skin_res)
{
  Resistances item_res;
  item_res.set_all_resistances_to(0.0);

  if (creature != nullptr)
  {
    ResistancesMap res = skin_res.get_resistances_map();

    for (const auto& res_pair : res)
    {
      double res_val = calculate_resistance_value(creature, res_pair.second);
      item_res.set_resistance_value(res_pair.first, res_val);
    }
  }

  return item_res;
}

// When applying a resistance via tanning, the base value is (resist / div),
// where divisor is based on the creature's tanning skill.
//
// Additional points (0.01) can potentially be added based on the
// creature's Tanning skill.
double TanningCalculator::calculate_resistance_value(CreaturePtr creature, const Resistance& resistance)
{
  double resist_val = 0.0;

  if (creature != nullptr)
  {
    int tanning_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING);
    double val = resistance.get_value();
    double divisor = 1.0;

    for (const pair<int, double>& r_pair : SKILL_VALUE_DIVISORS)
    {
      if (tanning_val >= r_pair.first)
      {
        divisor = r_pair.second;
        break;
      }
    }

    resist_val = (val / divisor);

    // Ensure that if this is a resist (> 0), there is a minimum value of 0.01.
    // That way, even with a large divisor, a small resistance can be carried
    // over.
    if (val > 0)
    {
      resist_val = std::max<double>(0.01, resist_val);
    }

    int potential_extra = calculate_potential_extra_resistance_points(creature);
    double extra = 0.0;

    if (resist_val > 0)
    {
      for (int i = 0; i < potential_extra; i++)
      {
        if (RNG::percent_chance(PCT_CHANCE_EXTRA_POINT))
        {
          extra += 0.01;
        }
        else
        {
          break;
        }
      }
    }

    resist_val += extra;
  }

  return resist_val;
}

// 1 extra potential point per 20 points of Tanning
int TanningCalculator::calculate_potential_extra_resistance_points(CreaturePtr creature)
{
  int extra = 0;

  if (creature != nullptr)
  {
    int val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING);
    extra = val / 15;
  }

  return extra;
}

#ifdef UNIT_TESTS
#include "unit_tests/TanningCalculator_test.cpp"
#endif
