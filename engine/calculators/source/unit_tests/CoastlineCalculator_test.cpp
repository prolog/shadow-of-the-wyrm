#include "gtest/gtest.h"

TEST(SW_Engine_Calc_CoastlineCalculator, calc_pct_chance_kelp_forest)
{
	CoastlineCalculator cc;
	vector<pair<Coordinate, int>> loc_and_chance = { { { 0, 0   }, 0 },
																									 { { 98, 98 }, 0 },
		                                               { { 50, 50 }, 0 },
																									 { { 70, 88 }, 8 },
																									 { { 30, 12 }, 8 },
																									 { { 93, 6  }, 28},
																									 { { 8, 6   }, 28}};
	int height = 100;

	for (const auto& lc : loc_and_chance)
	{
		EXPECT_EQ(lc.second, cc.calc_pct_chance_kelp_forest({ lc.first, height }));
	}
}

TEST(SW_Engine_Calc, calc_pct_chance_shoals)
{
	CoastlineCalculator cc;

	EXPECT_EQ(40, cc.calc_pct_chance_shoals());
}
