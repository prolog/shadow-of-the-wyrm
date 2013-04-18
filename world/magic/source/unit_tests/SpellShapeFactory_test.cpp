#include "gtest/gtest.h"

TEST(SL_World_Magic_SpellShapeFactory, shapes_return_correct_shape_type)
{
  for (int i = SPELL_SHAPE_TARGET_SELF; i < SPELL_SHAPE_LAST; i++)
  {
    SpellShapeType st = static_cast<SpellShapeType>(i);
    SpellShape ss = SpellShapeFactory::create_spell_shape(st);

    EXPECT_EQ(st, ss.get_spell_shape_type());
  }
}

TEST(SL_World_Magic_SpellShapeFactory, shapes_return_correct_directional_value)
{
  SpellShape ss_ts = SpellShapeFactory::create_spell_shape(SPELL_SHAPE_TARGET_SELF);
  EXPECT_FALSE(ss_ts.get_requires_direction());

  SpellShape ss_beam = SpellShapeFactory::create_spell_shape(SPELL_SHAPE_BEAM);
  EXPECT_TRUE(ss_beam.get_requires_direction());

  SpellShape ss_rbeam = SpellShapeFactory::create_spell_shape(SPELL_SHAPE_REFLECTIVE_BEAM);
  EXPECT_TRUE(ss_rbeam.get_requires_direction());

  SpellShape ss_cone = SpellShapeFactory::create_spell_shape(SPELL_SHAPE_CONE);
  EXPECT_TRUE(ss_cone.get_requires_direction());

  SpellShape ss_ball = SpellShapeFactory::create_spell_shape(SPELL_SHAPE_BALL);
  EXPECT_FALSE(ss_ball.get_requires_direction());

}
