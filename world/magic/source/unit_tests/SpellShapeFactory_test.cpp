#include "gtest/gtest.h"

TEST(SW_World_Magic_SpellShapeFactory, shapes_return_correct_shape_type)
{
  for (int i = static_cast<int>(SpellShapeType::SPELL_SHAPE_TARGET_SELF); i < static_cast<int>(SpellShapeType::SPELL_SHAPE_LAST); i++)
  {
    SpellShapeType st = static_cast<SpellShapeType>(i);
    SpellShape ss = SpellShapeFactory::create_spell_shape(st);

    EXPECT_EQ(st, ss.get_spell_shape_type());
  }
}

TEST(SW_World_Magic_SpellShapeFactory, shapes_return_correct_directional_value)
{
  SpellShape ss_ts = SpellShapeFactory::create_spell_shape(SpellShapeType::SPELL_SHAPE_TARGET_SELF);
  EXPECT_EQ(DirectionCategory::DIRECTION_CATEGORY_NONE, ss_ts.get_direction_category());

  SpellShape ss_beam = SpellShapeFactory::create_spell_shape(SpellShapeType::SPELL_SHAPE_BEAM);
  EXPECT_EQ(DirectionCategory::DIRECTION_CATEGORY_CARDINALORDINAL, ss_beam.get_direction_category());

  SpellShape ss_rbeam = SpellShapeFactory::create_spell_shape(SpellShapeType::SPELL_SHAPE_REFLECTIVE_BEAM);
  EXPECT_EQ(DirectionCategory::DIRECTION_CATEGORY_CARDINALORDINAL, ss_rbeam.get_direction_category());

  SpellShape ss_cone = SpellShapeFactory::create_spell_shape(SpellShapeType::SPELL_SHAPE_CONE);
  EXPECT_EQ(DirectionCategory::DIRECTION_CATEGORY_CARDINAL, ss_cone.get_direction_category());

  SpellShape ss_ball = SpellShapeFactory::create_spell_shape(SpellShapeType::SPELL_SHAPE_BALL);
  EXPECT_EQ(DirectionCategory::DIRECTION_CATEGORY_NONE, ss_ball.get_direction_category());

  SpellShape ss_storm = SpellShapeFactory::create_spell_shape(SpellShapeType::SPELL_SHAPE_STORM);
  EXPECT_EQ(DirectionCategory::DIRECTION_CATEGORY_NONE, ss_storm.get_direction_category());
}
