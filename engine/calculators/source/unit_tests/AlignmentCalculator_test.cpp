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