#include "gtest/gtest.h"

TEST(SW_World_Statistic, InitialValueIs1)
{
  Statistic stat;

  EXPECT_EQ(1, stat.get_base());
  EXPECT_EQ(1, stat.get_current());
}

TEST(SW_World_Statistic, Lowest)
{
  Statistic stat(30);
  stat.set_current(33);

  EXPECT_EQ(30, stat.get_lowest());

  Statistic stat2(25);
  stat2.set_current(15);

  EXPECT_EQ(15, stat2.get_lowest());
}

TEST(SW_World_Statistic, IsFull)
{
  Statistic stat(30);
  stat.set_current(30);

  EXPECT_TRUE(stat.get_full());

  stat.set_current(33);

  EXPECT_FALSE(stat.get_full());

  stat.set_current(10);

  EXPECT_FALSE(stat.get_full());
}

TEST(SW_World_Statistic, BaseValue)
{
  Statistic stat;

  stat.set_base(50);

  EXPECT_EQ(50, stat.get_base());

  stat.set_base(66);

  EXPECT_EQ(66, stat.get_base());
}

TEST(SW_World_Statistic, CurrentValue)
{
  Statistic stat;

  stat.set_current(44);

  EXPECT_EQ(44, stat.get_current());

  stat.set_current(99);

  EXPECT_EQ(99, stat.get_current());
}

TEST(SW_World_Statistic, serialization_id)
{
  Statistic stat;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_STATISTIC, stat.get_class_identifier());
}

TEST(SW_World_Statistic, saveload)
{
  Statistic stat(45);
  Statistic stat2;
  Marks m(32);
  stat.set_marks(m);

  ostringstream ss;

  stat.serialize(ss);

  istringstream iss(ss.str());

  stat2.deserialize(iss);

  EXPECT_TRUE(stat == stat2);
  EXPECT_EQ(32, stat2.get_marks().get_value());
}
