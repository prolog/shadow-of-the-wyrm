#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_FirePillar, serialization_id)
{
  FirePillar fire_pillar;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FIRE_PILLAR, fire_pillar.get_class_identifier());
}

