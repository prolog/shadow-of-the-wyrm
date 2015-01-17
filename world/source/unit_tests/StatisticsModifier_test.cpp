#include "gtest/gtest.h"

TEST(SL_World_StatisticsModifier, serialization_id)
{
  StatisticsModifier sm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_STATISTICS_MODIFIER, sm.get_class_identifier());
}

TEST(SL_World_StatisticsModifier, export_raw)
{
  vector<int> raw_values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  StatisticsModifier sm(raw_values);
  EXPECT_EQ(raw_values, sm.get_raw_values());
}

TEST(SL_World_StatisticsModifier, saveload)
{
  StatisticsModifier sm(1,2,3,4,5,6,7);
  sm.set_evade_modifier(3);
  sm.set_soak_modifier(4);

  StatisticsModifier sm2;

  EXPECT_FALSE(sm == sm2);

  ostringstream ss;

  sm.serialize(ss);

  istringstream iss(ss.str());

  sm2.deserialize(iss);

  EXPECT_TRUE(sm == sm2);
}
