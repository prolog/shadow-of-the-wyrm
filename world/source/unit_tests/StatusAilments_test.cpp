#include "gtest/gtest.h"

TEST(SL_World_StatusAilments, serialization_id)
{
  StatusAilments sa;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_STATUS_AILMENTS, sa.get_class_identifier());
}

TEST(SL_World_StatusAilments, saveload)
{
  set<string> ailments{"_poison", "_para"};
  StatusAilments sa, sa2;

  sa.set_override_defaults(true);
  sa.set_ailments(ailments);

  ostringstream ss;
  sa.serialize(ss);

  EXPECT_FALSE(sa == sa2);

  istringstream iss(ss.str());
  sa2.deserialize(iss);

  EXPECT_TRUE(sa == sa2);
}

