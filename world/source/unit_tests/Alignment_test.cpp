#include "gtest/gtest.h"

TEST(SL_World_Alignment, abrv_sid)
{
  Alignment a;

  EXPECT_EQ(TextKeys::ALIGNMENT_EVIL_ABRV, a.get_abbreviation_sid(ALIGNMENT_RANGE_EVIL));
  EXPECT_EQ(TextKeys::ALIGNMENT_GOOD_ABRV, a.get_abbreviation_sid(ALIGNMENT_RANGE_GOOD));
  EXPECT_EQ(TextKeys::ALIGNMENT_NEUTRAL_ABRV, a.get_abbreviation_sid(ALIGNMENT_RANGE_NEUTRAL));
}

TEST(SL_World_Alignment, align_sid)
{
  Alignment a;

  EXPECT_EQ(TextKeys::ALIGNMENT_EVIL, a.get_alignment_sid(ALIGNMENT_RANGE_EVIL));
  EXPECT_EQ(TextKeys::ALIGNMENT_GOOD, a.get_alignment_sid(ALIGNMENT_RANGE_GOOD));
  EXPECT_EQ(TextKeys::ALIGNMENT_NEUTRAL, a.get_alignment_sid(ALIGNMENT_RANGE_NEUTRAL));
}

TEST(SL_World_Alignment, default_for_range)
{
  Alignment a;

  EXPECT_EQ(0, a.get_default_alignment_for_range(ALIGNMENT_RANGE_NEUTRAL));
  EXPECT_EQ(-1600, a.get_default_alignment_for_range(ALIGNMENT_RANGE_EVIL));
  EXPECT_EQ(1600, a.get_default_alignment_for_range(ALIGNMENT_RANGE_GOOD));
}

TEST(SL_World_Alignment, set_values)
{
  Alignment a;

  EXPECT_EQ(0, a.get_alignment());

  a.set_alignment(1200);

  EXPECT_EQ(1200, a.get_alignment());

  a.set_alignment(26000);

  // Can't set above the range.
  EXPECT_EQ(1200, a.get_alignment());

  a.set_alignment(-1250);

  EXPECT_EQ(-1250, a.get_alignment());

  a.set_alignment(-3500);

  // Can't set below the range, either.
  EXPECT_EQ(-1250, a.get_alignment());
}

TEST(SL_World_Alignment, alignment_ranges)
{
  Alignment a;
  a.set_alignment(-2500);

  EXPECT_EQ(ALIGNMENT_RANGE_EVIL, a.get_alignment_range());

  a.set_alignment(-1000);

  EXPECT_EQ(ALIGNMENT_RANGE_EVIL, a.get_alignment_range());

  a.set_alignment(-50);

  EXPECT_EQ(ALIGNMENT_RANGE_NEUTRAL, a.get_alignment_range());

  a.set_alignment(1166);

  EXPECT_EQ(ALIGNMENT_RANGE_GOOD, a.get_alignment_range());
}

TEST(SL_World_Alignment, serialization_id)
{
  Alignment a;

  EXPECT_EQ(CLASS_ID_ALIGNMENT, a.get_class_identifier());
}

TEST(SL_World_Alignment, saveload)
{
  Alignment a, a2;
  a.set_alignment(1212);

  ostringstream ss;

  a.serialize(ss);

  istringstream iss(ss.str());

  a2.deserialize(iss);

  EXPECT_TRUE(a == a2);
}