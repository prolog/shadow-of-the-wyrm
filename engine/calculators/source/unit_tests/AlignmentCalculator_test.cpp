#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_AlignmentCalculator, calculate_alignment_for_sacrifice_on_coaligned_altar)
{
  AlignmentCalculator ac;

  int alignment = 1000;

  EXPECT_EQ(1010, ac.calculate_alignment_for_sacrifice_on_coaligned_altar(alignment, ALIGNMENT_RANGE_GOOD));

  alignment = 100;

  EXPECT_EQ(90, ac.calculate_alignment_for_sacrifice_on_coaligned_altar(alignment, ALIGNMENT_RANGE_NEUTRAL));

  alignment = -100;

  EXPECT_EQ(-90, ac.calculate_alignment_for_sacrifice_on_coaligned_altar(alignment, ALIGNMENT_RANGE_NEUTRAL));

  alignment = -1266;

  EXPECT_EQ(-1276, ac.calculate_alignment_for_sacrifice_on_coaligned_altar(alignment, ALIGNMENT_RANGE_EVIL));
}

TEST(SL_Engine_Calculators_AlignmentCalculator, calculate_alignment_for_sacrifice_on_crossaligned_altar)
{
  AlignmentCalculator ac;

  // This should never happen, but:
  // Cross-sacrificing as the same alignment should not change the current
  // value.
  EXPECT_EQ(1000, ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(1000, ALIGNMENT_RANGE_GOOD, ALIGNMENT_RANGE_GOOD));
  EXPECT_EQ(0, ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(0, ALIGNMENT_RANGE_NEUTRAL, ALIGNMENT_RANGE_NEUTRAL));
  EXPECT_EQ(-1000, ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(-1000, ALIGNMENT_RANGE_EVIL, ALIGNMENT_RANGE_EVIL));

  // Cross-sacrificing as good.
  int alignment = 1000;
  AlignmentRange cur_range = ALIGNMENT_RANGE_GOOD;
  AlignmentRange alt_range = ALIGNMENT_RANGE_NEUTRAL;

  EXPECT_EQ(750, ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(alignment, cur_range, alt_range));

  alt_range = ALIGNMENT_RANGE_EVIL;
  int exp_value = (1000 - static_cast<int>(250 * 1.5));
  EXPECT_EQ(exp_value, ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(alignment, cur_range, alt_range));

  // Cross-sacrificing as neutral.
  alignment = 200;
  cur_range = ALIGNMENT_RANGE_NEUTRAL;
  alt_range = ALIGNMENT_RANGE_GOOD;
  exp_value = 450;

  EXPECT_EQ(exp_value, ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(alignment, cur_range, alt_range));

  alt_range = ALIGNMENT_RANGE_EVIL;
  exp_value = -50;

  EXPECT_EQ(exp_value, ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(alignment, cur_range, alt_range));

  // Cross-sacrificing as evil.
  alignment = -1000;
  cur_range = ALIGNMENT_RANGE_EVIL;
  alt_range = ALIGNMENT_RANGE_NEUTRAL;
  exp_value = -750;

  EXPECT_EQ(exp_value, ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(alignment, cur_range, alt_range));

  alt_range = ALIGNMENT_RANGE_GOOD;
  exp_value = (-1000 + static_cast<int>(250 * 1.5));

  EXPECT_EQ(exp_value, ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(alignment, cur_range, alt_range));
}