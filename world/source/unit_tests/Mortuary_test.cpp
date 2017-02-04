#include "gtest/gtest.h"

// local prototype
void add_creatures_to_mortuary(Mortuary& m);

void add_creatures_to_mortuary(Mortuary& m)
{
  m.add_creature_kill("metal_slime");
  m.add_creature_kill("metal_slime");
  m.add_creature_kill("urok", true);

  m.add_creature_kill("dragon_cat_of_doom");
}

TEST(SW_World_Mortuary, death_toll)
{
  Mortuary m;

  add_creatures_to_mortuary(m);

  EXPECT_EQ(2, m.get_num_creature_killed("metal_slime"));
  EXPECT_EQ(1, m.get_num_creature_killed("dragon_cat_of_doom"));
  EXPECT_EQ(0, m.get_num_creature_killed("snipe"));

  EXPECT_EQ(4, m.get_num_creatures_killed());
}

TEST(SW_World_Mortuary, num_uniques_killed)
{
  Mortuary m;

  add_creatures_to_mortuary(m);

  EXPECT_EQ(1, m.get_num_uniques_killed());
}

TEST(SW_World_Mortuary, max_level_difference)
{
  Mortuary m;

  pair<int, string> actual = m.get_max_level_difference();
  
  EXPECT_EQ(-1, actual.first);
  EXPECT_EQ("", actual.second);

  m.set_max_level_difference(make_pair(2, "creature_1"));
  actual = m.get_max_level_difference();
  
  EXPECT_EQ(2, actual.first);
  EXPECT_EQ("creature_1", actual.second);
}

TEST(SW_World_Mortuary, serialization_id)
{
  Mortuary m;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MORTUARY, m.get_class_identifier());
}

TEST(SW_World_Mortuary, saveload)
{
  Mortuary m, m2;

  add_creatures_to_mortuary(m);

  ostringstream ss;

  m.serialize(ss);

  istringstream iss(ss.str());

  m2.deserialize(iss);

  EXPECT_TRUE(m == m2);

  EXPECT_EQ(1, m2.get_num_uniques_killed());
}

