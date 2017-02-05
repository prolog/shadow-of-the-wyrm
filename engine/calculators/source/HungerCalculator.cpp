#include "HungerCalculator.hpp"

const int HungerCalculator::HUNGER_DAMAGE_PER_TICK = 10;
const int HungerCalculator::PCT_CHANCE_HUNGER_WHILE_SATED = 15;

int HungerCalculator::calculate_hunger_damage(CreaturePtr creature, const ulonglong num_ticks) const
{
  return static_cast<int>(num_ticks * HUNGER_DAMAGE_PER_TICK);
}

int HungerCalculator::calculate_pct_chance_mark_health(const HungerLevel hl, const bool is_hungerless)
{
  int pct_chance = 0;

  if (hl == HungerLevel::HUNGER_LEVEL_NORMAL)
  {
    if (is_hungerless)
    {
      pct_chance = 20;
    }
    else
    {
      pct_chance = 100;
    }
  }

  return pct_chance;
}

int HungerCalculator::calculate_pct_chance_hunger_while_sated() const
{
  return PCT_CHANCE_HUNGER_WHILE_SATED;
}

#ifdef UNIT_TESTS
#include "unit_tests/HungerCalculator_test.cpp"
#endif
