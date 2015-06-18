#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Bed, serialization_id)
{
  Bed b;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BED, b.get_class_identifier());
}

