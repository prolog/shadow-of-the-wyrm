#include "gtest/gtest.h"

TEST(SL_Engine_Translators_DisplayItemTypeFactory, display_items_not_null_for_given_type)
{
  for (int i = static_cast<int>(ItemType::ITEM_TYPE_FIRST); i < static_cast<int>(ItemType::ITEM_TYPE_LAST); i++)
  {
    ItemType it = static_cast<ItemType>(i);
    DisplayItemTypePtr display_item = DisplayItemTypeFactory::create(static_cast<ItemType>(it));

    bool display_item_null = (display_item == NULL);
    
    EXPECT_FALSE(display_item_null);
  }
}
