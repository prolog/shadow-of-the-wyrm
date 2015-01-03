#include "gtest/gtest.h"

TEST(SL_World_Seasons_Autumn, serialization_id)
{
  Autumn autumn;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_AUTUMN, autumn.get_class_identifier());
}

TEST(SL_World_Seasons_Autumn, saveload)
{
  Autumn autumn, autumn2;

  ostringstream ss;

  autumn.serialize(ss);

  istringstream iss(ss.str());

  autumn2.deserialize(iss);

  EXPECT_TRUE(autumn == autumn2);
}

