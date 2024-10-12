#include "WaterBreathingCalculator.hpp"
#include "Random.hpp"

const int WaterBreathingCalculator::WB_DURATION = 45;
const int WaterBreathingCalculator::BASE_WB_PCT_CHANCE = 100;

int WaterBreathingCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  return BASE_WB_PCT_CHANCE;
}

// Water Breathing has a standard predictable wear-off time, since it's so
// dangerous once gone.
int WaterBreathingCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  return WB_DURATION;
}

