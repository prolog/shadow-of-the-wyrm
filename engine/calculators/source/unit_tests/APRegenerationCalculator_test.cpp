#include "gtest/gtest.h"
#include "AirTile.hpp"
#include "Bed.hpp"

TEST(SL_Engine_Calculators_APRegenerationCalculator, minutes_per_ap)
{
  CreaturePtr creature = std::make_shared<Creature>();
  TilePtr tile = std::make_shared<AirTile>();
  FeaturePtr bed = std::make_shared<Bed>();

  Statistic will(0);
  creature->set_willpower(will);

  tile->set_feature(bed);

  APRegenerationCalculator aprc;
  EXPECT_EQ(static_cast<uint>(15 * bed->get_ap_regeneration_multiplier()), aprc.calculate_minutes_per_ap_tick(creature, tile));

  will.set_base(20);
  will.set_current(20);
  creature->set_willpower(will);

  EXPECT_EQ(static_cast<uint>(15 * bed->get_ap_regeneration_multiplier() * 0.80), aprc.calculate_minutes_per_ap_tick(creature, tile));

  will.set_base(99);
  will.set_current(99);
  creature->set_willpower(will);

  EXPECT_EQ(4, aprc.calculate_minutes_per_ap_tick(creature, tile));
}

