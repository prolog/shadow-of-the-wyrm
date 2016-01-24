#include "gtest/gtest.h"

TEST(SW_World_Wand, serialization_id)
{
  Wand wand;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WAND, wand.get_class_identifier());
}

TEST(SW_World_Wand, saveload)
{
  Wand wand, wand2;

  wand.set_quantity(2);
  wand.set_effect_type(EffectType::EFFECT_TYPE_IDENTIFY);
  wand.set_range(12);
  wand.set_spell_shape_type(SpellShapeType::SPELL_SHAPE_REFLECTIVE_BEAM);
  Statistic charges(8);
  charges.set_current(4);
  wand.set_charges(charges);
  wand.set_colour(Colour::COLOUR_RED);

  ostringstream ss;

  wand.serialize(ss);

  istringstream iss(ss.str());

  wand2.deserialize(iss);

  EXPECT_TRUE(wand == wand2);
}

TEST(SW_World_Wand, no_effect_when_zero_charges)
{
  Wand wand;
  wand.set_effect_type(EffectType::EFFECT_TYPE_TELEPORT);
  wand.set_charges(14);

  EXPECT_EQ(EffectType::EFFECT_TYPE_TELEPORT, wand.get_effect_type());

  wand.set_charges(0);

  EXPECT_EQ(EffectType::EFFECT_TYPE_NULL, wand.get_effect_type());
}

TEST(SW_World_Wand, no_damage_when_zero_charges)
{
  Wand wand;
  wand.set_has_damage(true);
  wand.set_charges(7);

  EXPECT_TRUE(wand.get_has_damage());

  wand.set_charges(0);

  EXPECT_FALSE(wand.get_has_damage());
}

TEST(SW_World_Wand, no_range_when_zero_charges)
{
  Wand wand;
  wand.set_range(5);
  wand.set_charges(4);

  EXPECT_EQ(5, wand.get_range());

  wand.set_charges(0);

  EXPECT_EQ(0, wand.get_range());
}