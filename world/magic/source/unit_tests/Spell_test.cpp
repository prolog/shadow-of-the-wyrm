#include "gtest/gtest.h"

TEST(SL_World_Magic_Spell, equality_operator)
{
  Spell sp, sp2;

  sp.set_spell_id("foo");
  sp.set_spell_name_sid("spell_name_sid");
  sp.set_magic_category(SKILL_MAGIC_PRIMORDIAL);
  sp.set_ap_cost(5);
  sp.set_speed(4);

  EXPECT_FALSE(sp == sp2);

  sp = sp2;

  EXPECT_TRUE(sp == sp2);
}
