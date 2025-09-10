#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Hive, serialization_id)
{
  Symbol s('~', Colour::COLOUR_WHITE);
  Hive h(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_HIVE, h.get_class_identifier());
}

