#include "AlcoholCalculator.hpp"

using namespace std;

const uint AlcoholCalculator::BASE_MINUTES_FOR_ABSORPTION = 30;
const uint AlcoholCalculator::BASE_MINUTES_FOR_METABOLIZATION = 60;
const float AlcoholCalculator::BASE_METABOLISM_RATE = 0.5f;
const float AlcoholCalculator::DRUNK_BAC_THRESHOLD = 0.08f;
const float AlcoholCalculator::DEAD_BAC_THRESHOLD = 0.37f;

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

  absorption_by_sex = map<CreatureSex, float>{{CreatureSex::CREATURE_SEX_MALE, 1.0f}, {CreatureSex::CREATURE_SEX_FEMALE, 1.5f}};

  static_assert(CreatureSex::CREATURE_SEX_LAST == CreatureSex(2), "Creature sex has been updated - alcohol absorption and metabolism rate maps must be updated as well.");
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

// A creature is drunk if its BAC is greater than 0.08...
bool AlcoholCalculator::is_drunk(CreaturePtr creature)
{
  bool drunk = false;

  if (creature)
  {
    float bac = creature->get_blood().get_blood_alcohol_content();

    if (bac > DRUNK_BAC_THRESHOLD)
    { 
      drunk = true;
    }
  }

  return drunk;
}

bool AlcoholCalculator::is_dead_of_alcohol_poisoning(CreaturePtr creature)
{
  bool dead = false;

  if (creature)
  {
    float bac = creature->get_blood().get_blood_alcohol_content();

    if (bac > DEAD_BAC_THRESHOLD)
    {
      dead = true;
    }
  }

  return dead;
}

#ifdef UNIT_TESTS
#include "unit_tests/AlcoholCalculator_test.cpp"
#endif
