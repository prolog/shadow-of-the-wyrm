#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_RegularStatues, serialization_ids)
{
  PetrifiedCorpseStatue pet;

  EXPECT_EQ(CLASS_ID_PETRIFIED_CORPSE_STATUE, pet.get_class_identifier());
}

