#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_FirePillar, serialization_id)
{
  Symbol s('Y', Colour::COLOUR_WHITE);
  FirePillar fire_pillar(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FIRE_PILLAR, fire_pillar.get_class_identifier());
}

TEST(SW_World_Tiles_Features_FirePillar, blocking)
{
  Symbol s('Y', Colour::COLOUR_WHITE);
  FirePillar fire_pillar(s);

  EXPECT_TRUE(fire_pillar.get_is_blocking());
}
