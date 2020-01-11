#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Pulper, serialization_id)
{
  Symbol s(':', Colour::COLOUR_WHITE);
  Pulper p(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PULPER, p.get_class_identifier());
}

