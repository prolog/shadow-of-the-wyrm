#include "HPRegenerationCalculator.hpp"

const uint HPRegenerationCalculator::BASE_MINUTES_PER_HIT_POINT = 30;

uint HPRegenerationCalculator::calculate_minutes_per_hit_point(CreaturePtr creature, TilePtr tile)
{
  uint minutes_per_hit_point = BASE_MINUTES_PER_HIT_POINT;
  float multiplier = 1.0f;

  if (creature)
  {
    if (tile != nullptr)
    {
      multiplier *= tile->get_hp_regeneration_multiplier();

      FeaturePtr feature = tile->get_feature();

      if (feature != nullptr)
      {
        multiplier *= feature->get_hp_regeneration_multiplier();
      }
    }
  }

  minutes_per_hit_point = static_cast<uint>(minutes_per_hit_point * multiplier);
  return minutes_per_hit_point;
}

#ifdef UNIT_TESTS
#include "unit_tests/HPRegenerationCalculator_test.cpp"
#endif
