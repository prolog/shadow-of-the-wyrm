#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "Weapon.hpp"

TEST(SW_Engine_Items_HandsRequiredItemFilter, passes_test)
{
  HandsRequiredItemFilter hrif1(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED, 1);
  HandsRequiredItemFilter hrif2(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED, 2);
  HandsRequiredItemFilter hrif3(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND, 2);

  ItemPtr no_item;
  WeaponPtr weapon1 = std::make_shared<MeleeWeapon>();
  WeaponPtr weapon2 = std::make_shared<MeleeWeapon>();

  weapon1->set_hands_required(1);
  weapon2->set_hands_required(2);

  EXPECT_FALSE(hrif1.passes_filter(no_item));
  EXPECT_TRUE(hrif1.passes_filter(weapon1));
  EXPECT_FALSE(hrif1.passes_filter(weapon2));

  EXPECT_FALSE(hrif2.passes_filter(no_item));
  EXPECT_TRUE(hrif2.passes_filter(weapon1));
  EXPECT_TRUE(hrif2.passes_filter(weapon2));

  EXPECT_FALSE(hrif3.passes_filter(no_item));
  EXPECT_TRUE(hrif3.passes_filter(weapon1));
  EXPECT_FALSE(hrif3.passes_filter(weapon2));
}
