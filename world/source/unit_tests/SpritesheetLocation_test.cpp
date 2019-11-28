#include "gtest/gtest.h"

TEST(SW_World_SpritesheetLocation, object_creation_and_comparison)
{
  SpritesheetLocation sl;
  sl.set_index("abc");
  sl.set_row(1);
  sl.set_col(2);

  SpritesheetLocation sl2("abc", 1, 2);

  EXPECT_TRUE(sl == sl2);
}

TEST(SW_World_SpritesheetLocation, serialization_id)
{
  SpritesheetLocation sl;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SPRITESHEET_LOCATION, sl.get_class_identifier());
}

TEST(SW_World_SpritesheetLocation, saveload)
{
  SpritesheetLocation sl("abc", 1, 2);
  ostringstream ss;

  sl.serialize(ss);

  istringstream iss(ss.str());

  SpritesheetLocation sl2;
  sl2.deserialize(iss);

  EXPECT_TRUE(sl == sl2);
}
