#include "HPRegenerationCalculator.hpp"

const uint HPRegenerationCalculator::BASE_MINUTES_PER_HIT_POINT = 30;
const uint HPRegenerationCalculator::MIN_MINUTES_PER_HIT_POINT = 4;

uint HPRegenerationCalculator::calculate_minutes_per_hit_point(CreaturePtr creature, TilePtr tile)
{
  uint minutes_per_hit_point = BASE_MINUTES_PER_HIT_POINT;
  float multiplier = 1.0f;

  if (creature)
  {
    if (tile != nullptr)
    {
      multiplier *= tile->get_hp_regeneration_multiplier();
      multiplier *= get_health_multiplier(creature);

      FeaturePtr feature = tile->get_feature();

      if (feature != nullptr)
      {
        multiplier *= feature->get_hp_regeneration_multiplier();
      }
    }
  }

  minutes_per_hit_point = static_cast<uint>(minutes_per_hit_point * multiplier);

  return std::max<uint>(minutes_per_hit_point, MIN_MINUTES_PER_HIT_POINT);
}

float HPRegenerationCalculator::get_health_multiplier(CreaturePtr creature)
{
  float mult = 1.0f;

  if (creature != nullptr)
  {
    // - 0.01 to multiplier per point of Health.
    mult -= (0.01f * creature->get_health().get_current());
  }

  return mult;
}

#ifdef UNIT_TESTS
#include "unit_tests/HPRegenerationCalculator_test.cpp"
#endif
