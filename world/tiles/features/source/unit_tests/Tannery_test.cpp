#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Tannery, serialization_id)
{
  Tannery t;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TANNERY, t.get_class_identifier());
}

