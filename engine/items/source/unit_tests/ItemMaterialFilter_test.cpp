#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_Engine_Items_ItemMaterialFilter, passes_test)
{
  ItemMaterialFilter imf(MaterialType::MATERIAL_TYPE_WOOD);
  
  ItemPtr no_item;
  ItemPtr amulet = std::make_shared<Amulet>();
  amulet->set_material_type(MaterialType::MATERIAL_TYPE_GLASS);

  EXPECT_FALSE(imf.passes_filter(no_item));
  EXPECT_FALSE(imf.passes_filter(amulet));

  amulet->set_material_type(MaterialType::MATERIAL_TYPE_WOOD);

  EXPECT_TRUE(imf.passes_filter(amulet));
}

