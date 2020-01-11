#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Bed, serialization_id)
{
  Symbol s('~', Colour::COLOUR_WHITE);
  Bed b(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BED, b.get_class_identifier());
}

