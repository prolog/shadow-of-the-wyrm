#include "gtest/gtest.h"
#include <sstream>

TEST(SW_World_Tiles_Features_Pew, serialization_id)
{
  Pew pew;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PEW, pew.get_class_identifier());
}

// Just a properties test.
TEST(SW_World_Titles_Features_Pew, saveload)
{
  Pew pew;
  Pew pewpewpew;

  pew.set_additional_property("asdf", "123");
  std::stringstream ss;
  pew.serialize(ss);

  std::istringstream iss(ss.str());
  pewpewpew.deserialize(iss);

  EXPECT_TRUE(pew == pewpewpew);
  EXPECT_EQ("123", pewpewpew.get_additional_property("asdf"));
}
