#include "gtest/gtest.h"

TEST(SW_World_GenerationValues, rarity)
{
  GenerationValues gv;
  gv.set_rarity(Rarity::RARITY_RARE);

  EXPECT_EQ(Rarity::RARITY_RARE, gv.get_rarity());
}

TEST(SW_World_GenerationValues, maximum_nomax)
{
  GenerationValues gv;
  gv.set_maximum(-1);

  gv.incr_current();
  gv.incr_current();

  EXPECT_EQ(2, gv.get_current());
}

TEST(SW_World_GenerationValues, maximum)
{
  GenerationValues gv;
  gv.set_maximum(50);
  gv.set_current(48);

  gv.incr_current();
  gv.incr_current();

  EXPECT_EQ(50, gv.get_current());

  gv.incr_current();
  gv.incr_current();

  EXPECT_EQ(50, gv.get_current());
}

TEST(SW_World_GenerationValues, incr_value)
{
  GenerationValues gv;
  gv.set_maximum(50);

  gv.incr_current();
  gv.incr_current();

  EXPECT_EQ(2, gv.get_current());
}

TEST(SW_World_GenerationValues, decr_value)
{
  GenerationValues gv;
  gv.set_maximum(50);
  gv.set_current(12);

  gv.decr_current();
  gv.decr_current();

  EXPECT_EQ(10, gv.get_current());
}

TEST(SW_World_GenerationValues, danger)
{
  GenerationValues gv;
  gv.set_danger_level(12);

  EXPECT_EQ(12, gv.get_danger_level());
}

TEST(SW_World_GenerationValues, properties)
{
  GenerationValues gv;
  gv.set_property("a", "b");
  
  EXPECT_EQ("b", gv.get_property("a"));
}

TEST(SW_World_GenerationValues, serialization_id)
{
  GenerationValues gv;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_GENERATION_VALUES, gv.get_class_identifier());
}

TEST(SW_World_GenerationValues, saveload)
{
  GenerationValues gv;

  gv.set_current(5);
  gv.set_maximum(10);
  gv.set_danger_level(30);
  gv.set_rarity(Rarity::RARITY_RARE);
  gv.set_property("fdsa", "asdf");
  gv.set_property("Key", "Val");

  ostringstream ss;

  gv.serialize(ss);

  istringstream iss(ss.str());

  GenerationValues gv2;
  gv2.deserialize(iss);

  EXPECT_TRUE(gv == gv2);
}


