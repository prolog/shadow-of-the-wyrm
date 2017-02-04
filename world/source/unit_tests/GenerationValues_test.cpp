#include "gtest/gtest.h"

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


