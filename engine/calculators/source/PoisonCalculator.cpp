#include "PoisonCalculator.hpp"
#include "Random.hpp"

const int PoisonCalculator::BASE_POISON_DURATION_MEAN = 30;
const int PoisonCalculator::BASE_POISON_PCT_CHANCE = 25;

// The chance of being poisoned is reduced by 1 per every x points of
// health.
const int PoisonCalculator::BASE_POISON_CHANCE_HEALTH_MODIFIER = 5;

// Calculated mean for the Poisson distribution is reduced by 1 per every
// five points of health.
const int PoisonCalculator::HEALTH_DIVISOR = 5;

// The character is considered weak with a HEALTH <= 7.
const int PoisonCalculator::HEALTH_THRESHOLD_EXTRA_DAMAGE = 7;

// Calculate the chance that this creature gets poisoned.
int PoisonCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_POISON_PCT_CHANCE;

  if (creature)
  {
    int health_modifier = std::min<int>((creature->get_health().get_current() / BASE_POISON_CHANCE_HEALTH_MODIFIER), BASE_POISON_PCT_CHANCE);

    pct_chance -= health_modifier;
  }

  return pct_chance;
}

// Calculate the duration of the successful poisoning.
int PoisonCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  // Poison duration is described by a Poisson distribution, with the
  // average poisoning lasting about half an hour.
  PoissonDistribution p(calculate_poison_duration_mean(creature));
  int duration = p.next();

  return duration;
}

// Calculate the mean of the Poison Poisson distribution, which is affected
// by the creature's health.
int PoisonCalculator::calculate_poison_duration_mean(CreaturePtr creature) const
{
  int base_mean = BASE_POISON_DURATION_MEAN;
  return base_mean;
}

// Calculate the amount of damage that this creature takes per tick.
int PoisonCalculator::calculate_damage_per_tick(CreaturePtr creature) const
{
  int base_damage = 1;

  if (creature)
  {
    int cur_health = creature->get_health().get_current();

    if (cur_health <= HEALTH_THRESHOLD_EXTRA_DAMAGE)
    {
      base_damage++;
    }
  }

  return base_damage;
}

#ifdef UNIT_TESTS
#include "unit_tests/PoisonCalculator_test.cpp"
#endif