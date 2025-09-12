#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Hive, serialization_id)
{
  Symbol s('~', Colour::COLOUR_WHITE);
  Hive h(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_HIVE, h.get_class_identifier());
}

TEST(SW_World_Tiles_Features_Hive, saveload)
{
  Symbol s('~', Colour::COLOUR_WHITE);
  Hive h(s);

  int charges = 4;
  string drone_id = "insect";
  string leader_id = "big_insect";
  vector<string> item_ids = { "dirt", "more_dirt" };

  h.set_charges(charges);
  h.set_drone_id(drone_id);
  h.set_leader_id(leader_id);
  h.set_item_ids(item_ids);

  EXPECT_EQ(charges, h.get_charges());
  EXPECT_EQ(drone_id, h.get_drone_id());
  EXPECT_EQ(leader_id, h.get_leader_id());
  EXPECT_EQ(item_ids, h.get_item_ids());

  ostringstream ss;
  h.serialize(ss);

  istringstream iss(ss.str());

  Hive h2(s);
  h2.deserialize(iss);

  EXPECT_TRUE(h == h2);
}