#include "gtest/gtest.h"

TEST(SW_Engine_Creatures_CreatureFactory, set_name)
{
  ActionManager am;

  CreatureFactory cf;
  CreaturePtr c = cf.create_by_race_and_class(am, "", "", "Rodney", CreatureSex::CREATURE_SEX_MALE);

  EXPECT_EQ("Rodney", c->get_name());
}

TEST(SW_Engine_Creatures_CreatureFactory, select_race_id)
{
  CreatureFactory cf;
  vector<string> race_ids = {"elf", "dwarf", "human"};
  string default_race_id = "dwarf";

  EXPECT_EQ("dwarf", cf.select_race_id(race_ids, default_race_id));

  string race_id = cf.select_race_id(race_ids, "not_found");

  EXPECT_TRUE(std::find(race_ids.begin(), race_ids.end(), race_id) != race_ids.end());
}
