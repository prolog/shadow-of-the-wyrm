#include "gtest/gtest.h"

TEST(SL_World_Magic_IndividualSpellKnowledge, serialization_id)
{
  IndividualSpellKnowledge isk;

  EXPECT_EQ(CLASS_ID_INDIVIDUAL_SPELL_KNOWLEDGE, isk.get_class_identifier());
}

TEST(SL_World_Magic_IndividualSpellKnowledge, saveload)
{
  IndividualSpellKnowledge isk, isk2;

  isk.set_castings(3);
  isk.set_bonus(4);

  ostringstream ss;
  
  isk.serialize(ss);

  istringstream iss(ss.str());

  isk2.deserialize(iss);

  EXPECT_TRUE(isk == isk2);
}
