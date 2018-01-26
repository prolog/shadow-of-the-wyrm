#include "gtest/gtest.h"

TEST(SW_World_StartingLocation, serialization_id)
{
  StartingLocation sl;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_STARTING_LOCATION, sl.get_class_identifier());
}

TEST(SW_World_StartingLocation, saveload)
{
  StartingLocation sl(make_pair(3, 4), "cdefg");
  StartingLocation sl2;
  
  ostringstream oss;

  sl.serialize(oss);

  istringstream iss(oss.str());

  sl2.deserialize(iss);

  EXPECT_TRUE(sl == sl2);
}

