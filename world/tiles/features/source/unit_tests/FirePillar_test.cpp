#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_FirePillar, serialization_id)
{
  FirePillar fire_pillar;

  EXPECT_EQ(CLASS_ID_FIRE_PILLAR, fire_pillar.get_class_identifier());
}

