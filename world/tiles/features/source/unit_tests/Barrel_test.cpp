#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Barrel, pour)
{
  Barrel b;
  b.set_tap(true);
  b.set_pour_item_id("orcish_hooch");
  b.set_drinks(15);

  EXPECT_TRUE(b.pour());
  EXPECT_EQ(14, b.get_drinks());

  b.set_drinks(1);

  EXPECT_TRUE(b.pour());
  EXPECT_EQ(0, b.get_drinks());

  EXPECT_FALSE(b.pour());
  EXPECT_EQ(0, b.get_drinks());
}

TEST(SW_World_Tiles_Features_Barrel, can_pour)
{
  Barrel b;
  b.set_drinks(0);

  EXPECT_FALSE(b.can_pour());

  b.set_tap(true);

  EXPECT_FALSE(b.can_pour());

  b.set_pour_item_id("fairy_wine");

  EXPECT_FALSE(b.can_pour());

  b.set_drinks(22);

  EXPECT_TRUE(b.can_pour());
}

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
  barrel.set_drinks(8);

  ostringstream oss;

  barrel.serialize(oss);

  istringstream iss(oss.str());

  barrel2.deserialize(iss);

  EXPECT_TRUE(barrel == barrel2);

  EXPECT_TRUE(barrel2.get_pour_item_id() == "talisker");
  EXPECT_EQ(8, barrel2.get_drinks());
}

