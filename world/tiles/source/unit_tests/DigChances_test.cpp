#include "gtest/gtest.h"

TEST(SL_World_Tiles_DigChances, serialization_id)
{
  DigChances dc;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DIG_CHANCES, dc.get_class_identifier());
}

TEST(SL_World_Tiles_DigChances, set_values)
{
  DigChances dc;

  EXPECT_EQ(0, dc.get_pct_chance_undead());
  EXPECT_EQ(0, dc.get_pct_chance_item());

  dc.set_pct_chance_undead(12);
  dc.set_pct_chance_item(37);

  EXPECT_EQ(12, dc.get_pct_chance_undead());
  EXPECT_EQ(37, dc.get_pct_chance_item());

  DigChances dc2(55, 44);

  EXPECT_EQ(55, dc2.get_pct_chance_undead());
  EXPECT_EQ(44, dc2.get_pct_chance_item());
}

TEST(SL_World_Tiles_DigChances, saveload)
{
  DigChances dc(12, 24);
  DigChances dc2;

  ostringstream oss;
  dc.serialize(oss);

  istringstream iss(oss.str());

  dc2.deserialize(iss);

  EXPECT_EQ(12, dc2.get_pct_chance_undead());
  EXPECT_EQ(24, dc2.get_pct_chance_item());
}

