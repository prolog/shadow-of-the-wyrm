#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_RegularStatues, serialization_ids)
{
  Symbol s('?', Colour::COLOUR_WHITE);
  PetrifiedCorpseStatue pet(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PETRIFIED_CORPSE_STATUE, pet.get_class_identifier());
}

TEST(SW_World_Tiles_Features_RegularStatues, saveload)
{
  Symbol s('?', Colour::COLOUR_WHITE);
  PetrifiedCorpseStatue pcs(s);
  PetrifiedCorpseStatue pcs2(s);

  pcs.set_corpse_description_sid("foo");

  ostringstream oss;

  pcs.serialize(oss);

  istringstream iss(oss.str());

  pcs2.deserialize(iss);

  EXPECT_TRUE(pcs == pcs2);
}