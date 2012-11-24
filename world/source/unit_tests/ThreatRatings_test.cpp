#include "gtest/gtest.h"

TEST(SL_World_ThreatRatings, serialization_id)
{
  ThreatRatings tr;

  EXPECT_EQ(CLASS_ID_THREAT_RATINGS, tr.get_class_identifier());
}

TEST(SL_World_ThreatRatings, saveload)
{
  ThreatRatings tr, tr2;

  ostringstream ss;

  tr.serialize(ss);

  istringstream iss(ss.str());

  tr2.deserialize(iss);

  EXPECT_TRUE(tr == tr2);
}
