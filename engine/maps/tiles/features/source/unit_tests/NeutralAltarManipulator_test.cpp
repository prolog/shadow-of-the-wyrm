#include "gtest/gtest.h"
#include "NeutralAltar.hpp"

TEST(SW_Engine_Maps_Tiles_Features_NeutralAltarManipulator, action_key)
{
  FeaturePtr altar = std::make_shared<NeutralAltar>();
  NeutralAltarManipulator nap(altar);

  EXPECT_EQ(CreatureActionKeys::ACTION_DESECRATE_NEUTRAL, nap.get_creature_action_key());
}

