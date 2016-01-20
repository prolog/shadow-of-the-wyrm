#include "APRegenerationCalculator.hpp"
#include "ClassManager.hpp"
#include "RaceManager.hpp"

const uint APRegenerationCalculator::BASE_MINUTES_PER_AP_TICK = 15;
const uint APRegenerationCalculator::MIN_MINUTES_PER_AP_TICK = 4;

uint APRegenerationCalculator::calculate_minutes_per_ap_tick(CreaturePtr creature, TilePtr tile)
{
  uint minutes_per_ap_tick = BASE_MINUTES_PER_AP_TICK;
  float multiplier = 1.0f;

  if (creature)
  {
    if (tile != nullptr)
    {
      multiplier *= tile->get_ap_regeneration_multiplier();
      multiplier *= get_ap_tick_willpower_multiplier(creature);

      FeaturePtr feature = tile->get_feature();

      if (feature != nullptr)
      {
        multiplier *= feature->get_ap_regeneration_multiplier();
      }
    }
  }

  minutes_per_ap_tick = std::max(static_cast<uint>(minutes_per_ap_tick * multiplier), MIN_MINUTES_PER_AP_TICK);
  return minutes_per_ap_tick;
}

int APRegenerationCalculator::calculate_ap_per_tick(CreaturePtr creature)
{
  int ap_per_tick = 1;
  float mult = 1.0;

  if (creature)
  {
    RaceManager rm;
    ClassManager cm;

    RacePtr race = rm.get_race(creature->get_race_id());
    ClassPtr cr_class = cm.get_class(creature->get_class_id());

    if (race != nullptr)
    {
      mult *= race->get_ap_regen_multiplier();
    }

    if (cr_class != nullptr)
    {
      mult *= cr_class->get_ap_regen_multiplier();
    }

    ap_per_tick = std::max(1, static_cast<int>(std::ceil(ap_per_tick * mult)));
  }

  return ap_per_tick;
}

// A creature's base willpower multiplier is 1.0, with -0.01 per pt of will.
float APRegenerationCalculator::get_ap_tick_willpower_multiplier(CreaturePtr creature)
{
  float mult = 1.0f;

  if (creature != nullptr)
  {
    mult -= (0.01f * creature->get_willpower().get_current());
  }

  return mult;
}

#ifdef UNIT_TESTS
#include "unit_tests/APRegenerationCalculator_test.cpp"
#endif
