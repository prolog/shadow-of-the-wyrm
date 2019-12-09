#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Forge, serialization_id)
{
  Symbol s('&', Colour::COLOUR_WHITE);
  Forge f(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FORGE, f.get_class_identifier());
}

