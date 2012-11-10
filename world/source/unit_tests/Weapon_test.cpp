#include "gtest/gtest.h"

TEST(SL_World_Weapon, serialization_ids)
{
  MeleeWeapon melee;
  RangedWeapon ranged;

  EXPECT_EQ(CLASS_ID_MELEE_WEAPON, melee.get_class_identifier());
  EXPECT_EQ(CLASS_ID_RANGED_WEAPON, ranged.get_class_identifier());
}

