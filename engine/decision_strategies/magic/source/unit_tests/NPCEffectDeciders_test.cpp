#include "gtest/gtest.h"
#include "GeneratorUtils.hpp"

TEST(SW_Engine_DecisionStrategies_Magic_NPCEffectDeciders, decide_default)
{
	DefaultNPCEffectDecider dned;
	EXPECT_FALSE(dned.decide());
}

TEST(SW_Engine_DecisionStrategies_Magic_NPCEffectDeciders, decide_terrain)
{
	EffectTypeTerrainChecker ettc;
	CreaturePtr creature = std::make_shared<Creature>();
	Dimensions dim;
	MapPtr map = std::make_shared<Map>(dim);
	Coordinate start = { 0,0 };
	Coordinate end = { 19,79 };

	std::map<EffectType, TileType> tile_matches = { {EffectType::EFFECT_TYPE_WATER_BREATHING, TileType::TILE_TYPE_RIVER},
     																						  {EffectType::EFFECT_TYPE_FLYING, TileType::TILE_TYPE_AIR} };

	for (const auto& tm_pair : tile_matches)
	{
		GeneratorUtils::fill(map, start, end, tm_pair.second);
		TerrainNPCEffectDecider tned(creature, map, tm_pair.first);

		EXPECT_TRUE(tned.decide());
	}
}

TEST(SW_Engine_DecisionStrategies_Magic_NPCEffectDeciders, decide_modify_statistics)
{
	CreaturePtr creature = std::make_shared<Creature>();
	Dimensions dim;
	MapPtr map = std::make_shared<Map>(dim);

	// List of expected values and an associated spell shape and threat_exists
	// to use to configure the object instance.
	std::vector<std::pair<bool, std::pair<SpellShapeType, bool>>> exp_vals = { {true, {SpellShapeType::SPELL_SHAPE_TARGET_SELF, true}},
																																						 {false, {SpellShapeType::SPELL_SHAPE_TARGET_SELF, false}},
																																						 {false, {SpellShapeType::SPELL_SHAPE_BEAM, true}},
																																						 {false, {SpellShapeType::SPELL_SHAPE_CROSS, false}} };

	for (const auto& v : exp_vals)
	{
		ModifyStatisticsNPCEffectDecider msned(creature, map, v.second.first, v.second.second);
		EXPECT_EQ(v.first, msned.decide());
	}
}

TEST(SW_Engine_DecisionStrategies_Magic_NPCEffectDeciders, decide_cleansing)
{
	CreaturePtr creature = std::make_shared<Creature>();
	Dimensions dim;
	MapPtr map = std::make_shared<Map>(dim);

	CleansingNPCEffectDecider cned(creature, map);

	EXPECT_TRUE(cned.decide());

	map->set_property(MapProperties::MAP_PROPERTIES_CREATURE_GENERATION_RATE, "1.000");

	EXPECT_TRUE(cned.decide());

	map->set_property(MapProperties::MAP_PROPERTIES_CREATURE_GENERATION_RATE, "0.000");

	EXPECT_FALSE(cned.decide());
}
