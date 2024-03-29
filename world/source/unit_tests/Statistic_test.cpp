#include "gtest/gtest.h"

TEST(SW_World_Statistic, InitialValueIs1)
{
  Statistic stat;

  EXPECT_EQ(1, stat.get_base());
  EXPECT_EQ(1, stat.get_current());
}

TEST(SW_World_Statistic, OriginalValue)
{
  Statistic stat(17);

  stat.set_base_current(22);

  EXPECT_EQ(22, stat.get_base());
  EXPECT_EQ(22, stat.get_current());
  EXPECT_EQ(17, stat.get_original());
}

TEST(SW_World_Statistic, Maximum)
{
  Statistic stat;
  Statistic stat2(55);

  EXPECT_EQ(-1, stat.get_max());
  EXPECT_EQ(-1, stat2.get_max());

  Statistic stat3(55);
  stat3.set_max(55);

  stat3.set_current(57);

  EXPECT_EQ(55, stat3.get_current());

  stat3.set_base(59);

  EXPECT_EQ(55, stat3.get_base());

  stat3.set_max(66);

  stat3.set_base_current(62);

  EXPECT_EQ(62, stat3.get_base());
  EXPECT_EQ(62, stat3.get_current());
}

TEST(SW_World_Statistic, base_greater_than_max)
{
  Statistic st(55);
  st.set_max(99);

  st.set_base(105);

  EXPECT_EQ(55, st.get_base());

  st.set_base(105, SetStatisticFailure::SET_STATISTIC_FAILURE_IGNORE);

  EXPECT_EQ(55, st.get_base());

  st.set_base(105, SetStatisticFailure::SET_STATISTIC_FAILURE_TAKE_HIGHEST);
  
  EXPECT_EQ(st.get_max(), st.get_base());
}

TEST(SW_World_Statistic, current_greater_than_max)
{
  Statistic st(55);
  st.set_max(99);

  st.set_base_current(105);

  EXPECT_EQ(55, st.get_current());

  st.set_base_current(105, SetStatisticFailure::SET_STATISTIC_FAILURE_IGNORE);

  EXPECT_EQ(55, st.get_current());

  st.set_base_current(105, SetStatisticFailure::SET_STATISTIC_FAILURE_TAKE_HIGHEST);

  EXPECT_EQ(st.get_max(), st.get_current());
}

TEST(SW_World_Statistic, get_max_marks)
{
  Statistic test(16);
  test.get_marks_ref().set_value(14);

  EXPECT_FALSE(test.get_max_marks());

  test.get_marks_ref().set_value(16);

  EXPECT_TRUE(test.get_max_marks());
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

TEST(SW_World_Statistic, get_percent)
{
  Statistic stat(50);
  vector<pair<int, int>> val_and_expected = { {50, 100}, {25, 50}, {10, 20}, {100, 200} };

  for (const auto& ve : val_and_expected)
  {
    stat.set_current(ve.first);
    EXPECT_EQ(ve.second, stat.get_percent());
  }
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
  stat.set_base_current(55);

  ostringstream ss;

  stat.serialize(ss);

  istringstream iss(ss.str());

  stat2.deserialize(iss);

  EXPECT_TRUE(stat == stat2);
  EXPECT_EQ(32, stat2.get_marks().get_value());
  EXPECT_EQ(45, stat2.get_original());
  EXPECT_EQ(55, stat2.get_current());
}
