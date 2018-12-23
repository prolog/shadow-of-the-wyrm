#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Pulper, serialization_id)
{
  Pulper p;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PULPER, p.get_class_identifier());
}

