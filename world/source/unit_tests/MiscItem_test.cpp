#include "gtest/gtest.h"

TEST(SL_World_MiscItem, serialization_id)
{
  MiscItem misc_item;

  EXPECT_EQ(CLASS_ID_MISC_ITEM, misc_item.get_class_identifier());
}

TEST(SL_World_MiscItem, saveload)
{
  MiscItem misc1, misc2;

  misc1.set_quantity(42);

  ostringstream ss;

  misc1.serialize(ss);

  istringstream iss(ss.str());

  misc2.deserialize(iss);

  EXPECT_TRUE(misc1 == misc2);
}
