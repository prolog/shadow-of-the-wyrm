#include "APRegenerationCalculator.hpp"

const uint APRegenerationCalculator::BASE_MINUTES_PER_ARCANA_POINT = 40;

uint APRegenerationCalculator::calculate_minutes_per_arcana_point(CreaturePtr creature, TilePtr tile)
{
  uint minutes_per_arcana_point = BASE_MINUTES_PER_ARCANA_POINT;
  float multiplier = 1.0f;

  if (creature)
  {
    if (tile != nullptr)
    {
      multiplier *= tile->get_ap_regeneration_multiplier();

      FeaturePtr feature = tile->get_feature();

      if (feature != nullptr)
      {
        multiplier *= feature->get_ap_regeneration_multiplier();
      }
    }
  }

  minutes_per_arcana_point = static_cast<uint>(minutes_per_arcana_point * multiplier);
  return minutes_per_arcana_point;
}

#ifdef UNIT_TESTS
#include "unit_tests/APRegenerationCalculator_test.cpp"
#endif
