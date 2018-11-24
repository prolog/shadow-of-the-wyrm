#include "gtest/gtest.h"
#include <sstream>

TEST(SW_World_Tiles_Features_Sign, serialization_id)
{
  Sign sign("fdsa");

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SIGN, sign.get_class_identifier());
}

TEST(SW_World_Titles_Features_Sign, saveload)
{
  Sign sign("text_sid");
  Sign sign2("another_sid");

  std::stringstream ss;
  sign.serialize(ss);

  std::istringstream iss(ss.str());
  sign2.deserialize(iss);

  EXPECT_TRUE(sign == sign2);
  EXPECT_EQ("text_sid", sign2.get_text_sid());
}

