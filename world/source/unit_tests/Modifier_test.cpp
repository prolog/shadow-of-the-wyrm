#include "gtest/gtest.h"

TEST(SL_World_StatisticsModifier, serialization_id)
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

  Modifier m2;

  EXPECT_FALSE(m == m2);

  ostringstream ss;

  m.serialize(ss);

  istringstream iss(ss.str());

  m2.deserialize(iss);

  EXPECT_TRUE(m == m2);
}
