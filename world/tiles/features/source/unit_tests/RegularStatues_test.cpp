#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_RegularStatues, serialization_ids)
{
  PetrifiedCorpseStatue pet;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PETRIFIED_CORPSE_STATUE, pet.get_class_identifier());
}

TEST(SW_World_Tiles_Features_RegularStatues, saveload)
{
  PetrifiedCorpseStatue pcs, pcs2;

  pcs.set_corpse_description_sid("foo");

  ostringstream oss;

  pcs.serialize(oss);

  istringstream iss(oss.str());

  pcs2.deserialize(iss);

  EXPECT_TRUE(pcs == pcs2);
}