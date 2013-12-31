#include "AlcoholCalculator.hpp"

using namespace std;

const uint AlcoholCalculator::BASE_MINUTES_FOR_ABSORPTION = 30;
const uint AlcoholCalculator::BASE_MINUTES_FOR_METABOLIZATION = 60;
const float AlcoholCalculator::BASE_METABOLISM_RATE = 0.5f;
map<CreatureSex, float> AlcoholCalculator::absorption_by_sex;

AlcoholCalculator::AlcoholCalculator()
{
  if (absorption_by_sex.empty())
  {
    initialize_sex_based_maps();
  }
}

void AlcoholCalculator::initialize_sex_based_maps()
{
  absorption_by_sex.clear();

  absorption_by_sex = map<CreatureSex, float>{{CREATURE_SEX_MALE, 1.0f}, {CREATURE_SEX_FEMALE, 1.5f}};

  static_assert(CREATURE_SEX_LAST == 2, "Creature sex has been updated - alcohol absorption and metabolism rate maps must be updated as well.");
}

// Number of minutes required to pass before some alcohol is absorbed
// into the blood.
uint AlcoholCalculator::calculate_minutes_for_absorption(CreaturePtr creature)
{
  return BASE_MINUTES_FOR_ABSORPTION;
}

// Number of minutes required to pass before some alcohol is metabolized
// and removed from the bloodstream.
uint AlcoholCalculator::calculate_minutes_for_metabolization(CreaturePtr creature)
{
  return BASE_MINUTES_FOR_METABOLIZATION;
}

// Grams of alcohol to absorb per tick.
float AlcoholCalculator::calculate_grams_to_absorb(CreaturePtr creature)
{
  float to_absorb = 0.0f;

  if (creature)
  {
    float remaining = creature->get_grams_unabsorbed_alcohol();
    float base_rate = absorption_by_sex.find(creature->get_sex())->second;
    
    // Additional calculations (weight, etc.) will affect this later.
    to_absorb = base_rate;

    if (to_absorb > remaining)
    {
      to_absorb = remaining;
    }
  }

  return to_absorb;
}

// Grams of alcohol to metabolize per tick.  All creatures metabolize
// at approximately the same rate.
float AlcoholCalculator::calculate_grams_to_metabolize(CreaturePtr creature)
{
  return BASE_METABOLISM_RATE;
}

