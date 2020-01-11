#include "gtest/gtest.h"
#include "FeatureGenerator.hpp"

TEST(SW_Engine_Maps_Tiles_Features_GoodAltarManipulator, action_key)
{
  FeaturePtr altar = FeatureGenerator::generate_altar("abc123", AlignmentRange::ALIGNMENT_RANGE_GOOD);
  GoodAltarManipulator gap(altar);

  EXPECT_EQ(CreatureActionKeys::ACTION_DESECRATE_GOOD, gap.get_creature_action_key());
}

