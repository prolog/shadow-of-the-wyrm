#include "gtest/gtest.h"
#include "GeneratorUtils.hpp"

TEST(SW_Engine_DecisionStrategies_Magic_EffectTypeTerrainChecker, check_terrain_type)
{
	EffectTypeTerrainChecker ettc;
	CreaturePtr creature = std::make_shared<Creature>();
	Dimensions dim;
	MapPtr map = std::make_shared<Map>(dim);
	Coordinate start = { 0,0 };
	Coordinate end = { 19,79 };
	GeneratorUtils::fill(map, start, end, TileType::TILE_TYPE_FIELD);

	std::map<EffectType, TileType> tile_matches = {{EffectType::EFFECT_TYPE_WATER_BREATHING, TileType::TILE_TYPE_RIVER},
																  							 {EffectType::EFFECT_TYPE_FLYING, TileType::TILE_TYPE_AIR}};

	// All the expected false conditions: creature or map null, terrain not 
	// a match.
	EXPECT_FALSE(ettc.does_effect_match_terrain(nullptr, nullptr, EffectType::EFFECT_TYPE_WATER_BREATHING));
	EXPECT_FALSE(ettc.does_effect_match_terrain(creature, nullptr, EffectType::EFFECT_TYPE_WATER_BREATHING));
	EXPECT_FALSE(ettc.does_effect_match_terrain(nullptr, map, EffectType::EFFECT_TYPE_WATER_BREATHING));
	EXPECT_FALSE(ettc.does_effect_match_terrain(creature, map, EffectType::EFFECT_TYPE_WATER_BREATHING));
	EXPECT_FALSE(ettc.does_effect_match_terrain(creature, map, EffectType::EFFECT_TYPE_FLYING));

	for (const auto& tm_pair : tile_matches)
	{
		GeneratorUtils::fill(map, start, end, tm_pair.second);

		EXPECT_TRUE(ettc.does_effect_match_terrain(creature, map, tm_pair.first));
	}
}

