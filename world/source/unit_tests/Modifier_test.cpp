#include "gtest/gtest.h"

TEST(SL_World_Modifier, statuses)
{
  Modifier m;
  
  m.set_status("fdsa", true);
  m.set_status("asdf", false);

  EXPECT_EQ(true, m.get_status("fdsa"));
  EXPECT_EQ(true, m.has_status("fdsa"));

  EXPECT_EQ(false, m.get_status("asdf"));
  EXPECT_EQ(true, m.has_status("asdf"));

  EXPECT_EQ(false, m.get_status("abab"));
  EXPECT_EQ(false, m.has_status("abab"));
}

TEST(SL_World_Modifier, serialization_id)
{
  Modifier m;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MODIFIER, m.get_class_identifier());
}

TEST(SL_World_Modifier, export_raw)
{
  vector<int> raw_values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  Modifier m(raw_values);
  EXPECT_EQ(raw_values, m.get_raw_values());
}

TEST(SL_World_Modifier, saveload)
{
  Modifier m(1,2,3,4,5,6,7);
  m.set_evade_modifier(3);
  m.set_soak_modifier(4);

  m.set_status("asdf", true);

  Modifier m2;

  EXPECT_FALSE(m == m2);

  ostringstream ss;

  m.serialize(ss);

  istringstream iss(ss.str());

  m2.deserialize(iss);

  EXPECT_TRUE(m == m2);
}
