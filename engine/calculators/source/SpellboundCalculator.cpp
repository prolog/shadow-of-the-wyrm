#include "SpellboundCalculator.hpp"
#include "Random.hpp"

const int SpellboundCalculator::BASE_SPELLBOUND_DURATION_MEAN = 20;
const int SpellboundCalculator::BASE_SPELLBOUND_PCT_CHANCE = 10;

// For every 10 points of willpower, the percent chance of being spellbound
// (can only take non-movement actions) decreases by 1.
const int SpellboundCalculator::BASE_SPELLBOUND_CHANCE_WILLPOWER_MODIFIER = 10;

int SpellboundCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_SPELLBOUND_PCT_CHANCE;

  if (creature)
  {
    int willpower_bonus = creature->get_willpower().get_current() / BASE_SPELLBOUND_CHANCE_WILLPOWER_MODIFIER;

    double arcane_multiplier = std::max<double>(0.0, creature->get_resistances().get_resistance_value(DamageType::DAMAGE_TYPE_ARCANE));

    pct_chance -= willpower_bonus;
    pct_chance = static_cast<int>(pct_chance * arcane_multiplier);
  }

  return pct_chance;
}

int SpellboundCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_SPELLBOUND_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpellboundCalculator_test.cpp"
#endif
