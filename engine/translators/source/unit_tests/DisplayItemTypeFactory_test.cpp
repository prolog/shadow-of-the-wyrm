#include "gtest/gtest.h"

TEST(SL_Engine_Translators_DisplayItemTypeFactory, display_items_not_null_for_given_type)
{
  for (int it = ITEM_TYPE_FIRST; it < ITEM_TYPE_LAST; it++)
  {
    DisplayItemTypePtr display_item = DisplayItemTypeFactory::create(static_cast<ItemType>(it));

    bool display_item_null = (display_item == NULL);
    
    EXPECT_FALSE(display_item_null);
  }
}
