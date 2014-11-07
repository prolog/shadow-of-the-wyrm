#include "gtest/gtest.h"
#include "Weapon.hpp"
#include "Ring.hpp"
#include "Amulet.hpp"

TEST(SL_Engine_Items_SquishyEquipWornLocationFilter, passes_filter)
{
  SquishyEquipWornLocationFilter filter1(EQUIPMENT_WORN_RIGHT_FINGER);
  SquishyEquipWornLocationFilter filter2(EQUIPMENT_WORN_WIELDED);
  SquishyEquipWornLocationFilter filter3(EQUIPMENT_WORN_HEAD);

  ItemPtr no_item;

  EXPECT_FALSE(filter1.passes_filter(no_item));

  ItemPtr amulet = std::make_shared<Amulet>();
  amulet->set_worn_location(EQUIPMENT_WORN_NECK);

  EXPECT_FALSE(filter3.passes_filter(amulet));

  amulet->set_worn_location(EQUIPMENT_WORN_HEAD);

  EXPECT_TRUE(filter3.passes_filter(amulet));

  ItemPtr ring = std::make_shared<Ring>();
  ring->set_worn_location(EQUIPMENT_WORN_LEFT_FINGER);

  EXPECT_TRUE(filter1.passes_filter(ring));

  ring->set_worn_location(EQUIPMENT_WORN_RIGHT_FINGER);

  EXPECT_TRUE(filter1.passes_filter(ring));

  ring->set_worn_location(EQUIPMENT_WORN_FEET);

  EXPECT_FALSE(filter1.passes_filter(ring));

  ItemPtr weapon = std::make_shared<MeleeWeapon>();
  weapon->set_worn_location(EQUIPMENT_WORN_WIELDED);

  EXPECT_TRUE(filter2.passes_filter(weapon));

  weapon->set_worn_location(EQUIPMENT_WORN_OFF_HAND);

  EXPECT_TRUE(filter2.passes_filter(weapon));

  weapon->set_worn_location(EQUIPMENT_WORN_LEFT_FINGER);

  EXPECT_FALSE(filter2.passes_filter(weapon));
}

