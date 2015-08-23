#include "TimewalkCalculator.hpp"
#include "RNG.hpp"

const int TimewalkCalculator::BASE_TIMEWALK_PCT_CHANCE = 100;
const int TimewalkCalculator::BASE_TIMEWALK_WEAR_OFF_CHANCE_PER_TURN = 2;

int TimewalkCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  return BASE_TIMEWALK_PCT_CHANCE;
}

// This function is just here for completeness - timewalk by definition is done
// whenever time moves, so when the creature attacks, drops something, etc.
int TimewalkCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  return 0;
}

int TimewalkCalculator::calculate_pct_chance_wear_off_per_turn(CreaturePtr creature) const
{
  return BASE_TIMEWALK_WEAR_OFF_CHANCE_PER_TURN;
}

