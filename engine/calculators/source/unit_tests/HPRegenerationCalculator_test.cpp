#include "gtest/gtest.h"
#include "BarrowTile.hpp"
#include "Bed.hpp"

TEST(SL_Engine_Calculators_HPRegenerationCalculator, minutes_per_hp)
{
  CreaturePtr creature = std::make_shared<Creature>();
  TilePtr tile = std::make_shared<BarrowTile>();
  FeaturePtr bed = std::make_shared<Bed>();

  tile->set_feature(bed);

  HPRegenerationCalculator hprc;
  EXPECT_EQ(static_cast<uint>(30 * bed->get_hp_regeneration_multiplier()), hprc.calculate_minutes_per_hit_point(creature, tile));
}

