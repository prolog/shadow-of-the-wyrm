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
  wand.set_charges(8);

  ostringstream ss;

  wand.serialize(ss);

  istringstream iss(ss.str());

  wand2.deserialize(iss);

  EXPECT_TRUE(wand == wand2);
}

TEST(SL_World_Wand, no_effect_when_zero_charges)
{
  Wand wand;
  wand.set_effect_type(EFFECT_TYPE_TELEPORT);
  wand.set_charges(14);

  EXPECT_EQ(EFFECT_TYPE_TELEPORT, wand.get_effect_type());

  wand.set_charges(0);

  EXPECT_EQ(EFFECT_TYPE_NULL, wand.get_effect_type());
}