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

  ostringstream ss;

  sk.serialize(ss);

  istringstream iss(ss.str());
  sk2.deserialize(iss);

  EXPECT_TRUE(sk == sk2);
}

