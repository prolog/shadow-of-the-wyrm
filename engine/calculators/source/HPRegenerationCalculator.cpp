#include "HPRegenerationCalculator.hpp"
#include "ClassManager.hpp"
#include "RaceManager.hpp"

const uint HPRegenerationCalculator::BASE_MINUTES_PER_HP_TICK = 15;
const uint HPRegenerationCalculator::MIN_MINUTES_PER_HP_TICK = 4;

uint HPRegenerationCalculator::calculate_minutes_per_hp_tick(CreaturePtr creature, TilePtr tile)
{
  uint minutes_per_hp_tick = BASE_MINUTES_PER_HP_TICK;
  float multiplier = 1.0f;

  if (creature)
  {
    if (tile != nullptr)
    {
      multiplier *= tile->get_hp_regeneration_multiplier();
      multiplier *= get_hp_tick_health_multiplier(creature);

      FeaturePtr feature = tile->get_feature();

      if (feature != nullptr)
      {
        multiplier *= feature->get_hp_regeneration_multiplier();
      }
    }
  }

  minutes_per_hp_tick = static_cast<uint>(minutes_per_hp_tick * multiplier);

  return std::max<uint>(minutes_per_hp_tick, MIN_MINUTES_PER_HP_TICK);
}

int HPRegenerationCalculator::calculate_hp_per_tick(CreaturePtr creature)
{
  int hp_per_tick = 1;
  float mult = 1.0;

  if (creature)
  {
    RaceManager rm;
    ClassManager cm;

    RacePtr race = rm.get_race(creature->get_race_id());
    ClassPtr cr_class = cm.get_class(creature->get_class_id());

    if (race != nullptr)
    {
      mult *= race->get_hp_regen_multiplier();
    }

    if (cr_class != nullptr)
    {
      mult *= cr_class->get_hp_regen_multiplier();
    }

    hp_per_tick = std::max(1, static_cast<int>(std::ceil(hp_per_tick * mult)));

    Statistic hp = creature->get_hit_points();
    int b_hp = hp.get_base();
    int c_hp = hp.get_current();
    int d_hp = b_hp - c_hp;

    hp_per_tick = std::max(1, static_cast<int>(std::ceil(hp_per_tick * mult)));

    if (c_hp + hp_per_tick > b_hp)
    {
      hp_per_tick = d_hp;
    }
  }

  return hp_per_tick;
}

float HPRegenerationCalculator::get_hp_tick_health_multiplier(CreaturePtr creature)
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
