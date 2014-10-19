#include "gtest/gtest.h"

TEST(SL_Engine_AlignmentUtils, are_alignments_opposites)
{
  for (int i = ALIGNMENT_RANGE_EVIL; i <= ALIGNMENT_RANGE_GOOD; i++)
  {
    for (int j = ALIGNMENT_RANGE_EVIL; j <= ALIGNMENT_RANGE_GOOD; j++)
    {
      AlignmentRange a1 = static_cast<AlignmentRange>(i);
      AlignmentRange a2 = static_cast<AlignmentRange>(j);

      if ((a1 == ALIGNMENT_RANGE_EVIL && a2 == ALIGNMENT_RANGE_GOOD) || (a1 == ALIGNMENT_RANGE_GOOD && a2 == ALIGNMENT_RANGE_EVIL))
      {
        EXPECT_TRUE(AlignmentUtils::are_alignments_opposites(a1, a2));
      }
      else
      {
        EXPECT_FALSE(AlignmentUtils::are_alignments_opposites(a1, a2));
      }
    }
  }
}

