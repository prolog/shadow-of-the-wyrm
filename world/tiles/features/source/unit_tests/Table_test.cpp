#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Table, serialization_id)
{
  Symbol s('&', Colour::COLOUR_WHITE);
  Table t(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TABLE, t.get_class_identifier());
}

