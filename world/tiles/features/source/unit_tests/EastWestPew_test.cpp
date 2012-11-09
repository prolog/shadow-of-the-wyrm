#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_EastWestPew, serialization_id)
{
  EastWestPew ewpew;

  EXPECT_EQ(CLASS_ID_EAST_WEST_PEW, ewpew.get_class_identifier());
}

