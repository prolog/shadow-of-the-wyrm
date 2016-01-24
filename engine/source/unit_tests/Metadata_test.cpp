#include "gtest/gtest.h"

TEST(SW_Engine_Metadata, serialization_id)
{
  Metadata m;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_METADATA, m.get_class_identifier());
}

TEST(SW_Engine_Metadata, saveload)
{
  Metadata m, m2;

  ostringstream ss;

  m.serialize(ss);

  istringstream iss(ss.str());

  m2.deserialize(iss);

  EXPECT_TRUE(m == m2);
}
