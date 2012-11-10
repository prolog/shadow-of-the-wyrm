#include "gtest/gtest.h"

TEST(SL_World_Plant, serialization_id)
{
  Plant plant;

  EXPECT_EQ(CLASS_ID_PLANT, plant.get_class_identifier());
}
