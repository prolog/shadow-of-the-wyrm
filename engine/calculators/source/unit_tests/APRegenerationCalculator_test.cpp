#include "gtest/gtest.h"
#include "AirTile.hpp"
#include "Bed.hpp"

TEST(SL_Engine_Calculators_APRegenerationCalculator, minutes_per_ap)
{
  CreaturePtr creature = std::make_shared<Creature>();
  TilePtr tile = std::make_shared<AirTile>();
  FeaturePtr bed = std::make_shared<Bed>();

  tile->set_feature(bed);

  APRegenerationCalculator aprc;
  EXPECT_EQ(static_cast<uint>(40 * bed->get_ap_regeneration_multiplier()), aprc.calculate_minutes_per_arcana_point(creature, tile));
}

