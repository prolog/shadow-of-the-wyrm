#include "gtest/gtest.h"

TEST(SL_World_Weight, serialization_id)
{
  Weight weight;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WEIGHT, weight.get_class_identifier());
}

TEST(SL_World_Weight, saveload)
{
  Weight weight, weight2;

  weight.set_weight(1234);

  ostringstream ss;

  weight.serialize(ss);

  istringstream iss(ss.str());

  weight2.deserialize(iss);

  EXPECT_TRUE(weight == weight2);
}
