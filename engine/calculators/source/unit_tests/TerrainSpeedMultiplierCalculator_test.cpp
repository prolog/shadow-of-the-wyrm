#include "gtest/gtest.h"
#include "Boat.hpp"
#include "GeneratorUtils.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"

std::pair<CreaturePtr, MapPtr> create_creature_and_map_for_tsmc(const TileType fill_type);

std::pair<CreaturePtr, MapPtr> create_creature_and_map_for_tsmc(const TileType fill_type)
{
	CreaturePtr c = std::make_shared<Creature>();
	c->set_speed(50);

	Dimensions dim;
	MapPtr map = std::make_shared<Map>(dim);
	GeneratorUtils::fill(map, { 0,0 }, { 19, 79 }, fill_type);
	GameUtils::add_new_creature_to_map(Game::instance(), c, map, { 0,0 });

	return make_pair(c, map);
}

TEST(SW_World_Calculators_TerrainSpeedMultiplierCalculator, calculate_water)
{
	TerrainSpeedMultiplierCalculator tsmc;
	std::map<int, float> boating_multipliers = { {10, 0.95f}, {12, 0.94f}, {40, 0.8f}, {80, 0.6f}, {100, 0.5f} };
	std::vector<TileType> tile_types = { TileType::TILE_TYPE_SEA, TileType::TILE_TYPE_RIVER };
	ItemPtr boat = std::make_shared<Boat>();
	boat->set_id("b");

	for (const auto& tt : tile_types)
	{
		std::pair<CreaturePtr, MapPtr> creature_and_map = create_creature_and_map_for_tsmc(tt);

		for (const auto& b_pair : boating_multipliers)
		{
			creature_and_map.first->get_skills().set_value(SkillType::SKILL_GENERAL_BOATING, b_pair.first);
			EXPECT_FLOAT_EQ(1.0f, tsmc.calculate(creature_and_map.first, creature_and_map.second));

			creature_and_map.first->get_inventory()->add(boat);
			EXPECT_FLOAT_EQ(b_pair.second, tsmc.calculate(creature_and_map.first, creature_and_map.second));
			creature_and_map.first->get_inventory()->remove("b");
		}
	}
}

TEST(SW_World_Calculators_TerrainSpeedMultiplierCalculator, calculate_air_ground)
{
	TerrainSpeedMultiplierCalculator tsmc;
	std::map<int, float> boating_multipliers = { {10, 1.0f}, {12, 1.0f}, {40, 1.0f}, {80, 1.0f}, {100, 1.0f} };
	std::vector<TileType> tile_types = { TileType::TILE_TYPE_FIELD, TileType::TILE_TYPE_EVERGREEN_TREE, TileType::TILE_TYPE_MARSH, TileType::TILE_TYPE_AIR };

	for (const auto& tt : tile_types)
	{
		std::pair<CreaturePtr, MapPtr> creature_and_map = create_creature_and_map_for_tsmc(tt);

		for (const auto& b_pair : boating_multipliers)
		{
			creature_and_map.first->get_skills().set_value(SkillType::SKILL_GENERAL_BOATING, b_pair.first);
			EXPECT_FLOAT_EQ(b_pair.second, tsmc.calculate(creature_and_map.first, creature_and_map.second));
		}
	}
}
