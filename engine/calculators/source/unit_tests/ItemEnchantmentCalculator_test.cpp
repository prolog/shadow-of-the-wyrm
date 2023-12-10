#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_Engine_Calculators_ItemEnchantmentCalculators, calculate_pct_chance_brand)
{
  ItemEnchantmentCalculator iec;
  ItemPtr item = std::make_shared<Amulet>();

  // Nullptr - not brandable
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(1, nullptr));

  // Artifact - not brandable
  item->set_artifact(true);
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(1, item));

  // Brandable, not artifact, not branded - various chances.
  item->set_artifact(false);
  item->set_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDABLE, std::to_string(true));
  EXPECT_EQ(8, iec.calculate_pct_chance_brand(1, item));
  EXPECT_EQ(16, iec.calculate_pct_chance_brand(2, item));
  EXPECT_EQ(100, iec.calculate_pct_chance_brand(50000, item));
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(-1, item));

  item->set_status(ItemStatus::ITEM_STATUS_CURSED);
  EXPECT_EQ(4, iec.calculate_pct_chance_brand(1, item));
  EXPECT_EQ(1, iec.calculate_pct_chance_brand(0.25f, item));

  item->set_status(ItemStatus::ITEM_STATUS_BLESSED);
  EXPECT_EQ(18, iec.calculate_pct_chance_brand(1, item));
  EXPECT_EQ(36, iec.calculate_pct_chance_brand(2, item));


  item->set_status(ItemStatus::ITEM_STATUS_UNCURSED);

  // Not artifact, not brandable: 0% chance
  item->set_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDABLE, std::to_string(false));
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(1, item));

  // Not artifact, brandable, but already branded: 0% chance
  item->set_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDABLE, std::to_string(true));
  item->set_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDED, std::to_string(true));
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(1, item));
}
