#include "gtest/gtest.h"

TEST(SL_World_BoolStatistic, InitialValueIsTrue)
{
  BoolStatistic b_stat;

  EXPECT_TRUE(b_stat.get_base());
  EXPECT_TRUE(b_stat.get_current());
}

TEST(SL_World_BoolStatistic, BaseValue)
{
  BoolStatistic b_stat;

  b_stat.set_base(false);

  EXPECT_FALSE(b_stat.get_base());

  b_stat.set_base(true);

  EXPECT_TRUE(b_stat.get_base());
}

TEST(SL_World_BoolStatistic, CurrentValue)
{
  BoolStatistic b_stat;

  b_stat.set_current(true);

  EXPECT_TRUE(b_stat.get_current());

  b_stat.set_current(false);

  EXPECT_FALSE(b_stat.get_current());
}

TEST(SL_World_BoolStatistic, serialization_id)
{
  BoolStatistic stat;

  EXPECT_EQ(CLASS_ID_BOOL_STATISTIC, stat.get_class_identifier());
}

TEST(SL_World_BoolStatistic, saveload)
{
  BoolStatistic stat(false);
  BoolStatistic stat2;

  ostringstream ss;

  stat.serialize(ss);

  istringstream iss(ss.str());

  stat2.deserialize(iss);

  EXPECT_TRUE(stat == stat2);
}

