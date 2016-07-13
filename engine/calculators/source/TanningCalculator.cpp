#include "TanningCalculator.hpp"
#include "RNG.hpp"

using namespace std;

const int TanningCalculator::MAX_EVADE_BONUS = 10;
const int TanningCalculator::MAX_SOAK_BONUS = 5;
const int TanningCalculator::TANNING_EVADE_DECREMENT = 5;
const int TanningCalculator::TANNING_SOAK_DECREMENT = 5;
const int TanningCalculator::BASE_IMPROVEMENT_PCT = 10;
const int TanningCalculator::MAX_IMPROVEMENT_PCT = 100;
const int TanningCalculator::BASE_RESIST_DIVISOR = 5;
const vector<pair<int, double>> TanningCalculator::SKILL_VALUE_DIVISORS = {{100, 2.5}, {75, 3}, {50, 3.5}, {25, 4}, {0, 5.0}};
const int TanningCalculator::PCT_CHANCE_EXTRA_POINT = 60;

int TanningCalculator::calculate_evade_bonus(CreaturePtr creature)
{
  int ev_bonus = 0;
  vector<int> ev_probs = calculate_evade_probabilities(creature);

  for (int p : ev_probs)
  {
    if (RNG::percent_chance(p))
    {
      ev_bonus++;
    }
    else
    {
      break;
    }
  }

  return ev_bonus;
}

int TanningCalculator::calculate_soak_bonus(CreaturePtr creature)
{
  int sk_bonus = 0;
  vector<int> sk_probs = calculate_soak_probabilities(creature);

  for (int p : sk_probs)
  {
    if (RNG::percent_chance(p))
    {
      sk_bonus++;
    }
    else
    {
      break;
    }
  }

  return sk_bonus;
}

vector<int> TanningCalculator::calculate_evade_probabilities(CreaturePtr creature)
{
  vector<int> ev_probs;

  if (creature)
  {
    Skills& skills = creature->get_skills();
    int tanning_value = skills.get_value(SkillType::SKILL_GENERAL_TANNING);
    int crafting_value = skills.get_value(SkillType::SKILL_GENERAL_CRAFTING);

    int total_value = tanning_value + (crafting_value / 2);

    int p = min(MAX_IMPROVEMENT_PCT, total_value);

    for (int i = 0; i < MAX_EVADE_BONUS; i += 2)
    {
      if (p > BASE_IMPROVEMENT_PCT)
      {
        ev_probs.push_back(p);
      }
      else
      {
        ev_probs.push_back(BASE_IMPROVEMENT_PCT);
      }

      p -= TANNING_EVADE_DECREMENT;
    }
  }

  return ev_probs;
}

vector<int> TanningCalculator::calculate_soak_probabilities(CreaturePtr creature)
{
  vector<int> sk_probs;

  if (creature)
  {
    Skills& skills = creature->get_skills();
    int tanning_value = skills.get_value(SkillType::SKILL_GENERAL_TANNING);
    int crafting_value = skills.get_value(SkillType::SKILL_GENERAL_CRAFTING);

    int total_value = tanning_value + (crafting_value / 2);

    int p = min(MAX_IMPROVEMENT_PCT, total_value);

    for (int i = 0; i < MAX_SOAK_BONUS; i++)
    {
      if (p > BASE_IMPROVEMENT_PCT)
      {
        sk_probs.push_back(p);
      }
      else
      {
        sk_probs.push_back(BASE_IMPROVEMENT_PCT);
      }

      p -= TANNING_SOAK_DECREMENT;
    }
  }

  return sk_probs;
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
double TanningCalculator::calculate_resistance_value(CreaturePtr creature, ResistancePtr resistance)
{
  double resist_val = 0.0;

  if (creature != nullptr && resistance != nullptr)
  {
    int tanning_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING);
    double val = resistance->get_value();
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
