#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Pew, serialization_id)
{
  Pew pew;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PEW, pew.get_class_identifier());
}

