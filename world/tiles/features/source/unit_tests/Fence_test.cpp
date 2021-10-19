#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Fence, serialization_id)
{
  Symbol s('|', Colour::COLOUR_WHITE);
  Fence f(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FENCE, f.get_class_identifier());
}

TEST(SW_World_Tiles_Feature, blocking)
{
  Symbol s('|', Colour::COLOUR_WHITE);
  Fence f(s);

  EXPECT_TRUE(f.get_is_blocking());
}

