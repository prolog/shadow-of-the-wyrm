#include "gtest/gtest.h"

TEST(SL_World_Magic_SpellKnowledge, store_values)
{
  SpellKnowledge sk;

  EXPECT_EQ(0, sk.get_spell_knowledge("blast"));

  sk.set_spell_knowledge("big_blast", 15);

  EXPECT_EQ(15, sk.get_spell_knowledge("big_blast"));
}

TEST(SL_World_Magic_SpellKnowledge, serialization_id)
{
  SpellKnowledge sk;

  EXPECT_TRUE(sk.get_class_identifier() == CLASS_ID_SPELL_KNOWLEDGE);
}

TEST(SL_World_Magic_SpellKnowledge, saveload)
{
  SpellKnowledge sk, sk2;

  sk.set_spell_knowledge("foo", 2);
  sk.set_spell_knowledge("bar", 14);
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

  EXPECT_EQ(0, sk.count_spells_known());

  sk.set_spell_knowledge("frobozz", 12);

  EXPECT_EQ(1, sk.count_spells_known());

  sk.set_spell_knowledge("blaze", 3);
  sk.set_spell_knowledge("pontificate", 4);

  EXPECT_EQ(3, sk.count_spells_known());
}