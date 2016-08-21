#include "gtest/gtest.h"

TEST(SW_World_Weight, constructors)
{
  Weight w(10, 10);
  Weight w2(1672);

  EXPECT_EQ(170, w.get_weight());
  EXPECT_EQ(1672, w2.get_weight());
}

TEST(SW_World_Weight, operator_eq)
{
  Weight w1(10);
  Weight w2(10);
  Weight w3(12);

  EXPECT_TRUE(w1 == w2);
  EXPECT_FALSE(w1 == w3);
}

TEST(SW_World_Weight, operator_gthan)
{
  Weight w1(10);
  Weight w2(10);
  Weight w3(12);

  EXPECT_FALSE(w1 > w2);
  EXPECT_FALSE(w1 > w3);
  EXPECT_TRUE(w3 > w1);
}

TEST(SW_World_Weight, operator_lthan)
{
  Weight w1(10);
  Weight w2(10);
  Weight w3(12);

  EXPECT_FALSE(w1 < w2);
  EXPECT_TRUE(w1 < w3);
  EXPECT_FALSE(w3 < w1);
}

TEST(SW_World_Weight, serialization_id)
{
  Weight weight;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WEIGHT, weight.get_class_identifier());
}

TEST(SW_World_Weight, saveload)
{
  Weight weight, weight2;

  weight.set_weight(1234);

  ostringstream ss;

  weight.serialize(ss);

  istringstream iss(ss.str());

  weight2.deserialize(iss);

  EXPECT_TRUE(weight == weight2);
}
