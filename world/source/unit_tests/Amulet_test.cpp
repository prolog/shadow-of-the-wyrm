#include "gtest/gtest.h"

TEST(SW_World_Amulet, serialization_id)
{
  Amulet amulet;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_AMULET, amulet.get_class_identifier());
}

TEST(SW_World_Amulet, saveload)
{
  Amulet am, am2;

  ostringstream ss;

  am.set_soak(13);
  am.set_codex_description_sid("test!");

  am.serialize(ss);

  istringstream iss(ss.str());

  am2.deserialize(iss);

  EXPECT_TRUE(am == am2);
  EXPECT_EQ("test!", am2.get_codex_description_sid());
}
