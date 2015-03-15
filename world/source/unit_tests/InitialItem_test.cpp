#include "gtest/gtest.h"

TEST(SL_World_InitialItem, serialization_id)
{
  InitialItem ii;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_INITIAL_ITEM, ii.get_class_identifier());
}

TEST(SL_World_InitialItem, saveload)
{
  InitialItem ii;
  InitialItem ii2;

  ii.set_item_id("test");

  Dice dice;
  dice.set_dice_sides(5);
  dice.set_num_dice(4);
  dice.set_modifier(22);

  ii.set_item_quantity(dice);

  vector<pair<string, Dice>> random_item_ids = { { "abc", dice }, { "asdf", dice }, { "aaa", dice } };
  ii.set_random_item_ids(random_item_ids);

  pair<string, Dice> d_v = { "abc", dice };
  map<string, pair<string, Dice>> racial_rand = { { "r1", d_v }, { "r2", d_v } };
  ii.set_racial_item_ids(racial_rand);

  ostringstream oss;
  ii.serialize(oss);

  istringstream iss(oss.str());

  ii2.deserialize(iss);
  
  EXPECT_TRUE(ii == ii2);
}

