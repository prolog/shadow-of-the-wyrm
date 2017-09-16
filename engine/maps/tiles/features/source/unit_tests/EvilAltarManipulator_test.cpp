#include "gtest/gtest.h"
#include "EvilAltar.hpp"
TEST(SW_Engine_Maps_Tiles_Features_EvilAltarManipulator, action_key)
{
  FeaturePtr altar = std::make_shared<EvilAltar>();
  EvilAltarManipulator eap(altar);

  EXPECT_EQ(CreatureActionKeys::ACTION_DESECRATE_EVIL, eap.get_creature_action_key());
}

