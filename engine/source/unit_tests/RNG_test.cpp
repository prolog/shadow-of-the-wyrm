#include "gtest/gtest.h"

TEST(SL_Engine_RNG, Dice)
{
	for (int x = 0; x < 1000; x++)
	{
		int dice_result = RNG::dice(3, 6);
		EXPECT_LE(3, dice_result);
		EXPECT_GE(18, dice_result);

		int dice_result2 = RNG::dice(1, 1, 1);
		EXPECT_EQ(2, dice_result2);

    int dice_result3 = RNG::dice(1, 50, 50);
    EXPECT_LE(51, dice_result3);
    EXPECT_GE(100, dice_result3);

    int dice_result4 = RNG::dice(6, 1);
    EXPECT_LE(6, dice_result4);
	}
}

TEST(SL_Engine_RNG, Range)
{
	for (int x = 0; x < 1000; x++)
	{
		int range_result = RNG::range(10, 20);
		int range_result2 = RNG::range(0, 10, 10);
    int range_result3 = RNG::range(0, 5);
    int range_result4 = RNG::range(50, 52);
    int range_result5 = RNG::range(50, 52, 1);

		EXPECT_LE(10, range_result);
		EXPECT_GE(20, range_result);
		EXPECT_LE(10, range_result2);
		EXPECT_GE(20, range_result2);
    EXPECT_LE(0,  range_result3);
    EXPECT_GE(5,  range_result3);
    EXPECT_LE(50, range_result4);
    EXPECT_GE(52, range_result4);
    EXPECT_LE(51, range_result5);
    EXPECT_GE(53, range_result5);
	}
}
