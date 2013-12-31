#include "gtest/gtest.h"

TEST(SL_World_Blood, serialization_id)
{
  Blood b;
  EXPECT_EQ(CLASS_ID_BLOOD, b.get_class_identifier());
}

TEST(SL_World_Blood, saveload)
{
  Blood b, b2;

  b.set_litres(4.7f);
  b.set_grams_alcohol(5);

  ostringstream oss;

  b.serialize(oss);

  istringstream iss(oss.str());

  b2.deserialize(iss);

  EXPECT_TRUE(b == b2);
}

TEST(SL_World_Blood, increment_grams)
{
  Blood b;
  b.set_grams_alcohol(3);
  b.increment_grams_alcohol(2);

  EXPECT_EQ(5, b.get_grams_alcohol());
}

TEST(SL_World_Blood, decrement_grams)
{
  Blood b;
  b.set_grams_alcohol(5);
  b.decrement_grams_alcohol(4);

  EXPECT_EQ(1, b.get_grams_alcohol());

  b.decrement_grams_alcohol(4);

  EXPECT_EQ(0, b.get_grams_alcohol());
}

TEST(SL_World_Blood, BAC)
{
  // Humans actually have around five litres of blood - the 1.0 litres
  // below is just to test the calculation of BAC itself.
  Blood b;
  b.set_litres(1.0f);
  b.set_grams_alcohol(3);

  // Well and truly drunk!
  EXPECT_FLOAT_EQ(0.3f, b.get_blood_alcohol_content());

  // Barely feeling it!
  b.set_grams_alcohol(2);
  b.set_litres(5);
  EXPECT_FLOAT_EQ(0.04f, b.get_blood_alcohol_content());

  // Basically dead!
  b.set_grams_alcohol(35);
  b.set_litres(5);
  EXPECT_FLOAT_EQ(0.7f, b.get_blood_alcohol_content());

  // Decrement should recalc BAC
  b.decrement_grams_alcohol(33);
  EXPECT_FLOAT_EQ(0.04f, b.get_blood_alcohol_content());

  // Increment should recalc BAC
  b.increment_grams_alcohol(33);
  EXPECT_FLOAT_EQ(0.7f, b.get_blood_alcohol_content());

  // Test: one standard drink.
  b.set_grams_alcohol(13.6f);
  EXPECT_FLOAT_EQ(0.272f, b.get_blood_alcohol_content());
}

