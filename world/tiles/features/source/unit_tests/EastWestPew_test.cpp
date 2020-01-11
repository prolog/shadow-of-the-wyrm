#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_EastWestPew, serialization_id)
{
  Symbol s('|', Colour::COLOUR_WHITE);

  EastWestPew ewpew(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_EAST_WEST_PEW, ewpew.get_class_identifier());
}

