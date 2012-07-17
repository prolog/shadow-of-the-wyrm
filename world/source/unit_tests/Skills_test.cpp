#include "gtest/gtest.h"

// Can't instantiate Skill directly, so test the methods of a direct
// descendent.
TEST(SL_World_Skills_GeneralSkill, value)
{
  GeneralSkill gs;
  gs.set_value(5);

  EXPECT_EQ(5, gs.get_value());

  gs.increment_value();

  EXPECT_EQ(6, gs.get_value());
}

TEST(SL_World_Skills_GeneralSkill, marks)
{
  GeneralSkill gs;
  gs.set_marks(7);

  EXPECT_EQ(7, gs.get_marks());

  gs.increment_marks();

  EXPECT_EQ(8, gs.get_marks());
}

TEST(SL_World_Skills_GeneralSkill, threshold)
{
  GeneralSkill gs;
  gs.set_threshold(100);

  EXPECT_EQ(100, gs.get_threshold());
}

TEST(SL_World_Skills_GeneralSkill, category)
{
  GeneralSkill gs;
  EXPECT_EQ(SKILL_CATEGORY_GENERAL, gs.get_category());

  ArcherySkill archery;
  EXPECT_EQ(SKILL_CATEGORY_GENERAL, archery.get_category());
}

TEST(SL_World_Skills_WeaponSkill, category)
{
  WeaponSkill ws;
  EXPECT_EQ(SKILL_CATEGORY_MELEE, ws.get_category());

  AxesSkill axes;
  EXPECT_EQ(SKILL_CATEGORY_MELEE, axes.get_category());
}

TEST(SL_World_Skills_RangedWeaponSkill, category)
{
  RangedWeaponSkill rws;
  EXPECT_EQ(SKILL_CATEGORY_RANGED, rws.get_category());

  BowsSkill bows;
  EXPECT_EQ(SKILL_CATEGORY_RANGED, bows.get_category());
}

TEST(SL_World_Skills_MagicSkill, category)
{
  MagicSkill ms;
  EXPECT_EQ(SKILL_CATEGORY_MAGIC, ms.get_category());

  ArcaneMagicSkill arcane;
  EXPECT_EQ(SKILL_CATEGORY_MAGIC, arcane.get_category());
}
