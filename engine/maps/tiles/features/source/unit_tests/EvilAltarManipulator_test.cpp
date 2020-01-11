#include "gtest/gtest.h"
#include "FeatureGenerator.hpp"

TEST(SW_Engine_Maps_Tiles_Features_EvilAltarManipulator, action_key)
{
  FeaturePtr altar = FeatureGenerator::generate_altar("abc123", AlignmentRange::ALIGNMENT_RANGE_EVIL);
  EvilAltarManipulator eap(altar);

  EXPECT_EQ(CreatureActionKeys::ACTION_DESECRATE_EVIL, eap.get_creature_action_key());
}

