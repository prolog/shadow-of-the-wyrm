#include "gtest/gtest.h"

TEST(SW_Engine_MapExit, properties)
{
  MapExit me;

  EXPECT_FALSE(me.has_property("asdf"));

  me.set_property("asdf", "123");

  EXPECT_TRUE(me.has_property("asdf"));
  EXPECT_EQ("123", me.get_property("asdf"));
}

TEST(SW_Engine_MapExit, serialization_id)
{
  MapExit map_exit;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MAP_EXIT, map_exit.get_class_identifier());
}

TEST(SW_Engine_MapExit, saveload)
{
  MapExit me, me2;

  me.set_property("asdf", "fdsa");
  me.set_property("1", "2");
  me.set_map_id("aaa");

  ostringstream ss;
  me.serialize(ss);

  istringstream iss(ss.str());
  me2.deserialize(iss);

  EXPECT_TRUE(me == me2);
}