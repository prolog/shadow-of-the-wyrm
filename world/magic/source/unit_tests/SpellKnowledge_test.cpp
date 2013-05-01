#include "gtest/gtest.h"

TEST(SL_World_Magic_SpellKnowledge, store_values)
{
  SpellKnowledge sk;
  IndividualSpellKnowledge isk;
  isk.set_castings(15);

  EXPECT_EQ(0, sk.get_spell_knowledge("blast").get_castings());

  sk.set_spell_knowledge("big_blast", isk);

  EXPECT_EQ(15, sk.get_spell_knowledge("big_blast").get_castings());
}

TEST(SL_World_Magic_SpellKnowledge, serialization_id)
{
  SpellKnowledge sk;

  EXPECT_TRUE(sk.get_class_identifier() == CLASS_ID_SPELL_KNOWLEDGE);
}

TEST(SL_World_Magic_SpellKnowledge, saveload)
{
  SpellKnowledge sk, sk2;
  IndividualSpellKnowledge isk;
  isk.set_castings(5);
  isk.set_bonus(2);

  sk.set_spell_knowledge("foo", isk);
  sk.set_spell_knowledge("bar", isk);
  sk.set_most_recently_cast_spell_id("blasty");

  ostringstream ss;

  sk.serialize(ss);

  istringstream iss(ss.str());
  sk2.deserialize(iss);

  EXPECT_TRUE(sk == sk2);
}

TEST(SL_World_Magic_SpellKnowledge, count_spells_known)
{
  SpellKnowledge sk;

  IndividualSpellKnowledge isk;
  isk.set_castings(3);
  isk.set_bonus(4);

  EXPECT_EQ(0, sk.count_spells_known());

  sk.set_spell_knowledge("frobozz", isk);

  EXPECT_EQ(1, sk.count_spells_known());

  sk.set_spell_knowledge("blaze", isk);
  sk.set_spell_knowledge("pontificate", isk);

  EXPECT_EQ(3, sk.count_spells_known());
}