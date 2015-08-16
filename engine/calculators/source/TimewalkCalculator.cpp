#include "TimewalkCalculator.hpp"
#include "RNG.hpp"

const int TimewalkCalculator::BASE_TIMEWALK_PCT_CHANCE = 100;
const int TimewalkCalculator::BASE_TIMEWALK_WEAR_OFF_CHANCE_PER_TURN = 2;

int TimewalkCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  return BASE_TIMEWALK_PCT_CHANCE;
}

int TimewalkCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  // Timewalking is very powerful, but short-lived!
  int duration = RNG::range(5, 8);

  return duration;
}

int TimewalkCalculator::calculate_percent_chance_wear_off_per_turn(CreaturePtr creature) const
{
  return BASE_TIMEWALK_WEAR_OFF_CHANCE_PER_TURN;
}

