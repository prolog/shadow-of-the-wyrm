#include "gtest/gtest.h"
#include "GoodAltar.hpp"

TEST(SW_Engine_Maps_Tiles_Features_GoodAltarManipulator, action_key)
{
  FeaturePtr altar = std::make_shared<GoodAltar>();
  GoodAltarManipulator gap(altar);

  EXPECT_EQ(CreatureActionKeys::ACTION_DESECRATE_GOOD, gap.get_creature_action_key());
}

