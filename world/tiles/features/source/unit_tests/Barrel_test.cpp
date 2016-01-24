#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Barrel, serialization_id)
{
  Barrel barrel;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BARREL, barrel.get_class_identifier());
}

TEST(SW_World_Tiles_Features_Barrel, saveload)
{
  Barrel barrel, barrel2;

  barrel.set_tap(true);
  barrel.set_pour_item_id("talisker"); // A Birling Day essential.

  ostringstream oss;

  barrel.serialize(oss);

  istringstream iss(oss.str());

  barrel2.deserialize(iss);

  EXPECT_TRUE(barrel == barrel2);

  EXPECT_TRUE(barrel2.get_pour_item_id() == "talisker");
}
