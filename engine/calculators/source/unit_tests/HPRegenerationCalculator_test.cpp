#include "gtest/gtest.h"
#include "BarrowTile.hpp"
#include "Bed.hpp"

TEST(SL_Engine_Calculators_HPRegenerationCalculator, minutes_per_hp)
{
  CreaturePtr creature = std::make_shared<Creature>();
  Statistic health(0);
  creature->set_health(health);

  TilePtr tile = std::make_shared<BarrowTile>();
  FeaturePtr bed = std::make_shared<Bed>();

  tile->set_feature(bed);

  HPRegenerationCalculator hprc;
  EXPECT_EQ(static_cast<uint>(15 * bed->get_hp_regeneration_multiplier()), hprc.calculate_minutes_per_hp_tick(creature, tile));

  health.set_base(100);
  health.set_current(100);
  creature->set_health(health);

  EXPECT_EQ(4, hprc.calculate_minutes_per_hp_tick(creature, tile));
}

