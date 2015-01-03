#include "gtest/gtest.h"

TEST(SL_World_Statistic, InitialValueIs1)
{
  Statistic stat;

  EXPECT_EQ(1, stat.get_base());
  EXPECT_EQ(1, stat.get_current());
}

TEST(SL_World_Statistic, BaseValue)
{
  Statistic stat;

  stat.set_base(50);

  EXPECT_EQ(50, stat.get_base());

  stat.set_base(66);

  EXPECT_EQ(66, stat.get_base());
}

TEST(SL_World_Statistic, CurrentValue)
{
  Statistic stat;

  stat.set_current(44);

  EXPECT_EQ(44, stat.get_current());

  stat.set_current(99);

  EXPECT_EQ(99, stat.get_current());
}

TEST(SL_World_Statistic, serialization_id)
{
  Statistic stat;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_STATISTIC, stat.get_class_identifier());
}

TEST(SL_World_Statistic, saveload)
{
  Statistic stat(45);
  Statistic stat2;

  ostringstream ss;

  stat.serialize(ss);

  istringstream iss(ss.str());

  stat2.deserialize(iss);

  EXPECT_TRUE(stat == stat2);
}
