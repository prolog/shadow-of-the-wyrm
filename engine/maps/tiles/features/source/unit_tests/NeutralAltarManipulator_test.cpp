#include "gtest/gtest.h"
#include "FeatureGenerator.hpp"
#include "Features.hpp"

TEST(SW_Engine_Maps_Tiles_Features_NeutralAltarManipulator, action_key)
{
  FeaturePtr altar = FeatureGenerator::generate_altar("fdsa", AlignmentRange::ALIGNMENT_RANGE_NEUTRAL);
  NeutralAltarManipulator nap(altar);

  EXPECT_EQ(CreatureActionKeys::ACTION_DESECRATE_NEUTRAL, nap.get_creature_action_key());
}

