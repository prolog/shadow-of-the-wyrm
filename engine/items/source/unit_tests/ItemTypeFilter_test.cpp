#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "Food.hpp"

TEST(SW_Engine_Items_ItemTypeFilter, passes_filter)
{
  ItemTypeFilter itf(ItemType::ITEM_TYPE_AMULET);

  ItemPtr no_item;
  ItemPtr food = std::make_shared<Food>();
  ItemPtr amulet = std::make_shared<Amulet>();

  EXPECT_FALSE(itf.passes_filter(no_item));
  EXPECT_FALSE(itf.passes_filter(food));
  EXPECT_TRUE(itf.passes_filter(amulet));

  ItemTypeFilter itf2({ ItemType::ITEM_TYPE_AMULET, ItemType::ITEM_TYPE_FOOD });

  EXPECT_FALSE(itf2.passes_filter(no_item));
  EXPECT_TRUE(itf2.passes_filter(food));
  EXPECT_TRUE(itf2.passes_filter(amulet));
}
