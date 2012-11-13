#include "gtest/gtest.h"

TEST(SL_World_Potion, serialization_id)
{
  Potion potion;

  EXPECT_EQ(CLASS_ID_POTION, potion.get_class_identifier());
}

TEST(SL_World_Potion, saveload)
{
  Potion potion, potion2;

  potion.set_quantity(10);

  ostringstream ss;

  potion.serialize(ss);

  istringstream iss(ss.str());

  potion2.deserialize(iss);

  EXPECT_TRUE(potion == potion2);
}
