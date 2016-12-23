#include <algorithm>
#include "MineCalculator.hpp"

const int MineCalculator::BASE_CHANCE_MAGICI_SHARDS = 50;

int MineCalculator::calculate_pct_chance_magici_shards(const int danger_level) const
{
  int chance = BASE_CHANCE_MAGICI_SHARDS;

  if (danger_level >= 0)
  {
    chance += danger_level;
  }

  // In case danger level ever goes above 50, don't return absurd
  // chances for magici shards.
  chance = std::min<int>(100, chance);

  return chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/MineCalculator_test.cpp"
#endif

