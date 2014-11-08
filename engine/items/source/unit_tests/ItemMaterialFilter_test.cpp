#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SL_Engine_Items_ItemMaterialFilter, passes_test)
{
  ItemMaterialFilter imf(MATERIAL_TYPE_WOOD);
  
  ItemPtr no_item;
  ItemPtr amulet = std::make_shared<Amulet>();
  amulet->set_material_type(MATERIAL_TYPE_GLASS);

  EXPECT_FALSE(imf.passes_filter(no_item));
  EXPECT_FALSE(imf.passes_filter(amulet));

  amulet->set_material_type(MATERIAL_TYPE_WOOD);

  EXPECT_TRUE(imf.passes_filter(amulet));
}

