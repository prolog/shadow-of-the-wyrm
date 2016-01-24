#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Forge, serialization_id)
{
  Forge f;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FORGE, f.get_class_identifier());
}

