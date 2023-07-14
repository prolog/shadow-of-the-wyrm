#include "gtest/gtest.h"

TEST(SW_World_Religion_Religion, serialization_id)
{
  Religion r;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_RELIGION, r.get_class_identifier());
}

TEST(SW_World_Religion_Religion, saveload)
{
  Religion r, r2;
  DeityStatus d;
  d.set_piety(3456);

  r.set_deity_status("Bob", d);
  r.set_active_deity_id("Bob"); // Fnord

  ostringstream ss;

  r.serialize(ss);

  istringstream iss(ss.str());

  r2.deserialize(iss);

  EXPECT_TRUE(r == r2);
}

TEST(SW_World_Religion, starting_piety)
{
  Religion r;
  DeityStatus d;
  r.set_active_deity_id(ReligionConstants::DEITY_ID_GODLESS);
  EXPECT_EQ(100, d.get_piety());

  r.set_deity_status(ReligionConstants::DEITY_ID_GODLESS, d);
  DeityRelations dr = r.get_deity_relations();
  d = dr[ReligionConstants::DEITY_ID_GODLESS];
  EXPECT_EQ(0, d.get_piety());

  r.set_active_deity_id("the_trickster");
  dr = r.get_deity_relations();
  d = dr["the_trickster"];
  EXPECT_EQ(100, d.get_piety());

}

TEST(SW_World_Religion, piety_gain)
{
  Religion r;
  DeityStatus d;
  r.set_active_deity_id(ReligionConstants::DEITY_ID_GODLESS);
  r.set_deity_status(ReligionConstants::DEITY_ID_GODLESS, d);

  DeityRelations dr = r.get_deity_relations();
  d = dr[ReligionConstants::DEITY_ID_GODLESS];
  d.set_piety(50000);
  EXPECT_EQ(0, d.get_piety());
  EXPECT_TRUE(d.get_null());

  d = dr["a_valid_deity"];
  d.set_piety(4000);
  EXPECT_EQ(4000, d.get_piety());
  EXPECT_FALSE(d.get_null());
}