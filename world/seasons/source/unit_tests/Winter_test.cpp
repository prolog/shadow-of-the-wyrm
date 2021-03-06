#include "gtest/gtest.h"

TEST(SW_World_Seasons_Winter, serialization_id)
{
  Winter winter;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WINTER, winter.get_class_identifier());
}

TEST(SW_World_Seasons_Winter, foragables_present)
{
  Winter winter;

  EXPECT_TRUE(winter.get_foragables().empty() == false);
}


TEST(SW_World_Seasons_Winter, saveload)
{
  Winter winter, winter2;

  ostringstream ss;

  winter.serialize(ss);

  istringstream iss(ss.str());

  winter2.deserialize(iss);

  EXPECT_TRUE(winter == winter2);
}

