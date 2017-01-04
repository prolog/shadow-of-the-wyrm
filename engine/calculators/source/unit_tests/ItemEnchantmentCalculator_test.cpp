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
  EXPECT_EQ(15, iec.calculate_pct_chance_brand(1, item));
  EXPECT_EQ(30, iec.calculate_pct_chance_brand(2, item));
  EXPECT_EQ(100, iec.calculate_pct_chance_brand(50000, item));
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(-1, item));

  // Not artifact, not brandable: 0% chance
  item->set_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDABLE, std::to_string(false));
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(1, item));

  // Not artifact, brandable, but already branded: 0% chance
  item->set_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDABLE, std::to_string(true));
  item->set_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDED, std::to_string(true));
  EXPECT_EQ(0, iec.calculate_pct_chance_brand(1, item));

}
