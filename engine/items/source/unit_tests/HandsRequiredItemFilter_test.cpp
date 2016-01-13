#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "Weapon.hpp"

TEST(SL_Engine_Items_HandsRequiredItemFilter, passes_test)
{
  HandsRequiredItemFilter hrif1(1);
  HandsRequiredItemFilter hrif2(2);

  ItemPtr no_item;
  ItemPtr amulet = std::make_shared<Amulet>();
  WeaponPtr weapon1 = std::make_shared<MeleeWeapon>();
  WeaponPtr weapon2 = std::make_shared<MeleeWeapon>();

  weapon1->set_hands_required(1);
  weapon2->set_hands_required(2);

  EXPECT_FALSE(hrif1.passes_filter(no_item));
  EXPECT_TRUE(hrif1.passes_filter(amulet));
  EXPECT_TRUE(hrif1.passes_filter(weapon1));
  EXPECT_FALSE(hrif1.passes_filter(weapon2));

  EXPECT_FALSE(hrif2.passes_filter(no_item));
  EXPECT_TRUE(hrif2.passes_filter(amulet));
  EXPECT_TRUE(hrif2.passes_filter(weapon1));
  EXPECT_TRUE(hrif2.passes_filter(weapon2));
}
