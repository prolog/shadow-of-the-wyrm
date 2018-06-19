#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Table, serialization_id)
{
  Table t;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TABLE, t.get_class_identifier());
}

