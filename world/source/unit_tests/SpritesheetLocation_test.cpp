#include "gtest/gtest.h"

TEST(SW_World_SpritesheetLocation, object_creation_and_comparison_coord)
{
  SpritesheetLocation sl;
  sl.set_index("abc");
  sl.set_coordinate(make_pair(1, 2));

  SpritesheetLocation sl2("abc", make_pair(1,2));

  EXPECT_TRUE(sl == sl2);
}

TEST(SW_World_SpritesheetLocation, object_creation_and_comparison_reference_id)
{
  SpritesheetLocation sl;
  sl.set_index("abc");
  sl.set_reference_id("closed_door");

  SpritesheetLocation sl2("abc", "closed_door");

  EXPECT_TRUE(sl == sl2);
}

TEST(SW_World_SpritesheetLocation, reference_id)
{
  SpritesheetLocation sl("abc123", make_pair(3,3));
  SpritesheetLocation sl2("abc123", "closed_door");

  EXPECT_FALSE(sl.uses_reference_id());
  EXPECT_TRUE(sl2.uses_reference_id());
}

TEST(SW_World_SpritesheetLocation, serialization_id)
{
  SpritesheetLocation sl;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SPRITESHEET_LOCATION, sl.get_class_identifier());
}

TEST(SW_World_SpritesheetLocation, saveload_coord)
{
  SpritesheetLocation sl("abc", make_pair(1,2));
  ostringstream ss;

  sl.serialize(ss);

  istringstream iss(ss.str());

  SpritesheetLocation sl2;
  sl2.deserialize(iss);

  EXPECT_TRUE(sl == sl2);
}

TEST(SW_World_SpritesheetLocation, saveload_refid)
{
  SpritesheetLocation sl("abc", "ref_id");
  ostringstream ss;

  sl.serialize(ss);

  istringstream iss(ss.str());

  SpritesheetLocation sl2;
  sl2.deserialize(iss);

  EXPECT_TRUE(sl == sl2);
}
