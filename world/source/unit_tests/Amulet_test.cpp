#include "gtest/gtest.h"

TEST(SL_World_Amulet, serialization_id)
{
  Amulet amulet;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_AMULET, amulet.get_class_identifier());
}

TEST(SL_World_Amulet, saveload)
{
  Amulet am, am2;

  ostringstream ss;

  am.set_soak(13);

  am.serialize(ss);

  istringstream iss(ss.str());

  am2.deserialize(iss);

  EXPECT_TRUE(am == am2);
}
