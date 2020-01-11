#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Fountain, serialization_id)
{
  Symbol s('~', Colour::COLOUR_WHITE);
  Fountain fountain(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FOUNTAIN, fountain.get_class_identifier());
}

