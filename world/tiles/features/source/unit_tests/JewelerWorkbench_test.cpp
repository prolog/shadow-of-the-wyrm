#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_JewelerWorkbench, serialization_id)
{
  Symbol s('&', Colour::COLOUR_WHITE);
  JewelerWorkbench j(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH, j.get_class_identifier());
}

