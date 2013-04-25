#include "gtest/gtest.h"
#include "SpellShapeFactory.hpp"

TEST(SL_World_Magic_Spell, equality_operator)
{
  Spell sp, sp2;

  sp.set_spell_id("foo");
  sp.set_spell_name_sid("spell_name_sid");
  sp.set_player_cast_message_sid("player_cast");
  sp.set_monster_cast_message_sid("monster_cast");
  sp.set_colour(COLOUR_GREEN);
  sp.set_magic_category(SKILL_MAGIC_PRIMORDIAL);
  sp.set_ap_cost(5);
  sp.set_speed(4);
  sp.set_range(1);
  SpellShape shape = SpellShapeFactory::create_spell_shape(SPELL_SHAPE_BALL);
  sp.set_shape(shape);
  sp.set_has_damage(true);
  sp.set_effect(EFFECT_TYPE_HEALING);

  Damage damage(1,5,3,DAMAGE_TYPE_ARCANE);

  sp.set_damage(damage);

  EXPECT_FALSE(sp == sp2);

  sp = sp2;

  EXPECT_TRUE(sp == sp2);
}
