#include "TanningCalculator.hpp"
#include "RNG.hpp"

using namespace std;

const int TanningCalculator::MAX_EVADE_BONUS = 10;
const int TanningCalculator::MAX_SOAK_BONUS = 5;
const int TanningCalculator::TANNING_EVADE_DECREMENT = 5;
const int TanningCalculator::TANNING_SOAK_DECREMENT = 5;
const int TanningCalculator::BASE_IMPROVEMENT_PCT = 10;
const int TanningCalculator::MAX_IMPROVEMENT_PCT = 100;

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
    int tanning_value = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING);
    int p = min(MAX_IMPROVEMENT_PCT, tanning_value);

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
    int tanning_value = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING);
    int p = min(MAX_IMPROVEMENT_PCT, tanning_value);

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

#ifdef UNIT_TESTS
#include "unit_tests/TanningCalculator_test.cpp"
#endif
