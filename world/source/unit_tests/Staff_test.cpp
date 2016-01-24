#include "gtest/gtest.h"

TEST(SW_World_Staff, serialization_id)
{
  Staff staff;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_STAFF, staff.get_class_identifier());
}

TEST(SW_World_Staff, saveload)
{
  Staff staff, staff2;

  staff.set_quantity(3);
  staff.set_description_sid("fdsafdsa");

  ostringstream ss;

  staff.serialize(ss);

  istringstream iss(ss.str());

  staff2.deserialize(iss);

  EXPECT_TRUE(staff == staff2);
}
