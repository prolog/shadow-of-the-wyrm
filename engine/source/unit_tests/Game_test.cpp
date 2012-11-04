#include "gtest/gtest.h"

TEST(SL_Engine_Game, serialization_id)
{
  Game g;

  EXPECT_EQ(CLASS_ID_GAME, g.get_class_identifier());
}

