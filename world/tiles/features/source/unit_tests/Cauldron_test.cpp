#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Cauldron, serialization_id)
{
  Symbol s('~', Colour::COLOUR_WHITE);
  Cauldron c(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CAULDRON, c.get_class_identifier());
}

