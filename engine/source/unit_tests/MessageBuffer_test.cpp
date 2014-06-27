#include "gtest/gtest.h"

TEST(SL_Engine_MessageBuffer, serialization_id)
{
  MessageBuffer mb;
  EXPECT_EQ(CLASS_ID_MESSAGE_BUFFER, mb.get_class_identifier());
}

TEST(SL_Engine_MessageBuffer, saveload)
{
  MessageBuffer mb;
  MessageBuffer mb2;

  ostringstream ss;

  mb.serialize(ss);

  istringstream iss(ss.str());

  mb2.deserialize(iss);

  EXPECT_TRUE(mb == mb2);
}

