#include "gtest/gtest.h"

TEST(SL_World_Scroll, serialization_id)
{
  Scroll scroll;

  EXPECT_EQ(CLASS_ID_SCROLL, scroll.get_class_identifier());
}

TEST(SL_World_Scroll, saveload)
{
  Scroll scroll, scroll2;

  scroll.set_material_type(MATERIAL_TYPE_IVORY);

  ostringstream ss;

  scroll.serialize(ss);

  istringstream iss(ss.str());

  scroll2.deserialize(iss);

  EXPECT_TRUE(scroll == scroll2);
}
