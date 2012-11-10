#include "gtest/gtest.h"

TEST(SL_World_MiscItem, serialization_id)
{
  MiscItem misc_item;

  EXPECT_EQ(CLASS_ID_MISC_ITEM, misc_item.get_class_identifier());
}
