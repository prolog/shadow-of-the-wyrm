#include "gtest/gtest.h"

TEST(SL_World_Wand, serialization_id)
{
  Wand wand;

  EXPECT_EQ(CLASS_ID_WAND, wand.get_class_identifier());
}

TEST(SL_World_Wand, saveload)
{
  Wand wand, wand2;

  wand.set_quantity(2);
  wand.set_effect_type(EFFECT_TYPE_IDENTIFY);
  wand.set_range(12);
  wand.set_spell_shape_type(SPELL_SHAPE_REFLECTIVE_BEAM);

  ostringstream ss;

  wand.serialize(ss);

  istringstream iss(ss.str());

  wand2.deserialize(iss);

  EXPECT_TRUE(wand == wand2);
}
