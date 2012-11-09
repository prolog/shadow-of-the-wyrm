#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Trap, serialization_id)
{
  Trap trap;

  EXPECT_EQ(CLASS_ID_TRAP, trap.get_class_identifier());
}

