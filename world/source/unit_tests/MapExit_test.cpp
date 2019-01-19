#include "gtest/gtest.h"

TEST(SW_Engine_MapExit, coord)
{
  Coordinate c = {1,1};

  MapExit me;

  EXPECT_FALSE(me.has_coordinate());

  me.set_coordinate(c);

  EXPECT_TRUE(me.has_coordinate());
  EXPECT_EQ(c, me.get_coordinate());
}

TEST(SW_Engine_MapExit, properties)
{
  MapExit me;

  EXPECT_FALSE(me.has_property("asdf"));

  me.set_property("asdf", "123");

  ScriptDetails sd;
  sd.set_chance(44);
  sd.set_script("test.lua");

  me.add_event_script("aaa", sd);

  EXPECT_TRUE(me.has_property("asdf"));
  EXPECT_EQ("123", me.get_property("asdf"));
  EXPECT_EQ("test.lua", me.get_event_script("aaa").get_script());
  EXPECT_EQ(44, me.get_event_script("aaa").get_chance());
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
  me.set_coordinate({3,4});

  ostringstream ss;
  me.serialize(ss);

  istringstream iss(ss.str());
  me2.deserialize(iss);

  EXPECT_TRUE(me == me2);
}