#include "gtest/gtest.h"
#include <sstream>

TEST(SW_World_Tiles_Features_Sign, serialization_id)
{
  Symbol s('+', Colour::COLOUR_WHITE);
  Sign sign(s, "fdsa");

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SIGN, sign.get_class_identifier());
}

TEST(SW_World_Titles_Features_Sign, saveload)
{
  Symbol s('_', Colour::COLOUR_WHITE);
  Sign sign(s, "text_sid");
  Sign sign2(s, "another_sid");

  std::stringstream ss;
  sign.serialize(ss);

  std::istringstream iss(ss.str());
  sign2.deserialize(iss);

  EXPECT_TRUE(sign == sign2);
}

