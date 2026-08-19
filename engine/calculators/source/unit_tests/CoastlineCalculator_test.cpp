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

TEST(SW_Engine_Calc_CoastlineCalculator, calc_pct_chance_shoals)
{
	CoastlineCalculator cc;

	EXPECT_EQ(40, cc.calc_pct_chance_shoals());
}

TEST(SW_Engine_Calc_CoastlineCalculator, calc_pct_chance_shoals_open_water)
{
	CoastlineCalculator cc;

	EXPECT_EQ(0, cc.calc_pct_chance_shoals({}));
	EXPECT_EQ(10, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_MOUNTAINS}));
	EXPECT_EQ(20, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_MOUNTAINS, TileType::TILE_TYPE_MOUNTAINS}));
	EXPECT_EQ(7, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_HILLS}));
	EXPECT_EQ(5, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_MARSH}));
	EXPECT_EQ(12, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_HILLS, TileType::TILE_TYPE_MARSH}));
	EXPECT_EQ(1, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_FIELD}));
	EXPECT_EQ(1, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_FOREST}));
	EXPECT_EQ(1, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_SCRUB}));
	EXPECT_EQ(1, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_DESERT}));
	EXPECT_EQ(4, cc.calc_pct_chance_shoals({TileType::TILE_TYPE_FIELD, TileType::TILE_TYPE_FOREST, TileType::TILE_TYPE_SCRUB, TileType::TILE_TYPE_DESERT}));
}
