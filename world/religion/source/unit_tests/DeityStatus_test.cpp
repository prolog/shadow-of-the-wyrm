#include "gtest/gtest.h"

TEST(SL_World_Religion_DeityStatus, serialization_id)
{
  DeityStatus ds;

  EXPECT_EQ(CLASS_ID_DEITY_STATUS, ds.get_class_identifier());
}

TEST(SL_World_Religion_DeityStatus, saveload)
{
  DeityStatus ds1, ds2;

  ds1.set_piety(1234);

  ostringstream ss;

  ds1.serialize(ss);

  istringstream iss(ss.str());

  ds2.deserialize(iss);

  EXPECT_TRUE(ds1 == ds2);
}
