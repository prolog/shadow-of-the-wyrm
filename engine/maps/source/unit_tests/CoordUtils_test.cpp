#include "gtest/gtest.h"

TEST(SL_Engine_CoordUtils, incr)
{
  Dimensions d; // Bog standard 20x80.
  Coordinate c(0, 0);
  Coordinate cprime(0, 1);

  EXPECT_EQ(cprime, CoordUtils::incr(c, d));

  c.second = 79;
  cprime.first = 1;
  cprime.second = 0;

  EXPECT_EQ(cprime, CoordUtils::incr(c, d));

  c.first = 19;
  c.second = 79;

  EXPECT_EQ(CoordUtils::end(), CoordUtils::incr(c, d));
}

TEST(SL_Engine_CoordUtils, end_coordinate)
{
  EXPECT_TRUE(CoordUtils::is_end(CoordUtils::end()));
}
