#include "gtest/gtest.h"
#include "SpellShapeFactory.hpp"

TEST(SW_World_Magic_Spell, properties)
{
  Spell sp;
  string key = "abc";
  string value = "123";

  EXPECT_FALSE(sp.has_property(key));

  sp.set_property(key, value);

  EXPECT_TRUE(sp.has_property(key));
  EXPECT_EQ(value, sp.get_property(key));
}

TEST(SW_World_Magic_Spell, equality_operator)
{
  Spell sp, sp2;

  sp.set_spell_id("foo");
  sp.set_spell_name_sid("spell_name_sid");
  sp.set_player_cast_message_sid("player_cast");
  sp.set_monster_cast_message_sid("monster_cast");
  sp.set_colour(Colour::COLOUR_GREEN);
  sp.set_magic_category(SkillType::SKILL_MAGIC_PRIMORDIAL);
  sp.set_ap_cost(5);
  sp.set_property("abc123", "fdsafdsafdsa");
  sp.set_speed(4);
  sp.set_range(1);
  SpellShape shape = SpellShapeFactory::create_spell_shape(SpellShapeType::SPELL_SHAPE_BALL, 1);
  sp.set_shape(shape);
  sp.set_has_damage(true);
  sp.set_effect(EffectType::EFFECT_TYPE_HEALING);

  Modifier m({ 1, 2, 3, 4, 5 });
  sp.set_modifier(m);

  Damage damage(1,5,3,DamageType::DAMAGE_TYPE_ARCANE, {}, false, false, false, false, false, false, false, 0, {});

  sp.set_damage(damage);

  EXPECT_FALSE(sp == sp2);

  sp = sp2;

  EXPECT_TRUE(sp == sp2);
}
