#include "gtest/gtest.h"

TEST(SW_World_Symbol, char_data_no_spritesheet)
{
  Symbol s('a', Colour::COLOUR_RED);

  EXPECT_FALSE(s.get_uses_spritesheet());
}

TEST(SW_World_Symbol, object_creation_and_comparison)
{
  SpritesheetLocation sl("abc", 1, 2);

  Symbol s;
  s.set_symbol('f');
  s.set_colour(Colour::COLOUR_BLUE);
  s.set_spritesheet_location(sl);

  Symbol s2('f', Colour::COLOUR_BLUE, sl);

  EXPECT_TRUE(s == s2);
}

TEST(SW_World_Symbol, serialization_id)
{
  Symbol s;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SYMBOL, s.get_class_identifier());
}

TEST(SW_World_Symbol, saveload)
{
  Symbol s('f', Colour::COLOUR_BLUE, { "abc123", 1, 2 });
  Symbol s2;

  ostringstream ss;
  s.serialize(ss);

  istringstream iss(ss.str());

  s2.deserialize(iss);

  EXPECT_TRUE(s == s2);
}