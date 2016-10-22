#include "gtest/gtest.h"

TEST(SW_World_Magic_SpellShape, object_values)
{
  SpellShape ss(SpellShapeType::SPELL_SHAPE_CONE, DirectionCategory::DIRECTION_CATEGORY_CARDINAL, 3);

  EXPECT_EQ(SpellShapeType::SPELL_SHAPE_CONE, ss.get_spell_shape_type());
  EXPECT_EQ(DirectionCategory::DIRECTION_CATEGORY_CARDINAL, ss.get_direction_category());
  EXPECT_EQ(3, ss.get_radius());
}

TEST(SW_World_Magic_SpellShape, get_spell_situation)
{
  SpellShape ss(SpellShapeType::SPELL_SHAPE_CONE, DirectionCategory::DIRECTION_CATEGORY_CARDINAL, 3);
  EXPECT_EQ(SpellSituationType::SPELL_SITUATION_EXTERNAL, ss.get_spell_situation());

  SpellShape ss2;
  EXPECT_EQ(SpellSituationType::SPELL_SITUATION_INTERNAL, ss2.get_spell_situation());
}

