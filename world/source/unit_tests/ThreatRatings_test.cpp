#include "gtest/gtest.h"

TEST(SL_World_ThreatRatings, serialization_id)
{
  ThreatRatings tr;

  EXPECT_EQ(CLASS_ID_THREAT_RATINGS, tr.get_class_identifier());
}

