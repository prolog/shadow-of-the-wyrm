#include "gtest/gtest.h"

TEST(SL_World_Plant, serialization_id)
{
  Plant plant;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PLANT, plant.get_class_identifier());
}

TEST(SL_World_Plant, saveload)
{
  Plant plant, plant2;

  plant.set_description_sid("donut tree");

  ostringstream ss;

  plant.serialize(ss);

  istringstream iss(ss.str());

  plant2.deserialize(iss);

  EXPECT_TRUE(plant == plant2);
}
