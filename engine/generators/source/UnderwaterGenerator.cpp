#include "UnderwaterGenerator.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "ItemManager.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RockTile.hpp"
#include "RockyEarthTile.hpp"
#include "RNG.hpp"
#include "SeabedTile.hpp"

using namespace std;

const int UnderwaterGenerator::PCT_CHANCE_ROCKY_BOTTOM = 25;
const int UnderwaterGenerator::PCT_CHANCE_CORPSES = 5;
const int UnderwaterGenerator::PCT_CHANCE_SPRINGS_IVORY = 10;
const int UnderwaterGenerator::PCT_CHANCE_UNDERWATER_ITEMS = 20;
const int UnderwaterGenerator::PCT_CHANCE_UNDERWATER_ITEMS_LOWER = 2;
const int UnderwaterGenerator::PCT_CHANCE_UNDERWATER_ITEMS_UPPER = 8;
const int UnderwaterGenerator::PCT_CHANCE_ROCK_LOWER = 10;
const int UnderwaterGenerator::PCT_CHANCE_ROCK_UPPER = 80;

UnderwaterGenerator::UnderwaterGenerator(MapPtr above_map, const string& map_exit_id)
: Generator(map_exit_id, TileType::TILE_TYPE_SEA), above_water_map(above_map)
{
	init_underwater_item_ids();
}

void UnderwaterGenerator::init_underwater_item_ids()
{
	underwater_item_ids = { {ItemIdKeys::ITEM_ID_CLAY_POT, 20}, {ItemIdKeys::ITEM_ID_STONE, 100} };

	if (RNG::percent_chance(PCT_CHANCE_CORPSES))
	{
		underwater_item_ids.push_back(make_pair(ItemIdKeys::ITEM_ID_INTACT_SKELETON, 100));
	}
}

MapPtr UnderwaterGenerator::generate(const Dimensions& dim)
{
	MapPtr result_map = std::make_shared<Map>(dim);
	result_map->set_permanent(true);
	int generation_rate = 0;
	int rock_generation_rate = 0;
	string shipwreck_val = get_additional_property(TileProperties::TILE_PROPERTY_UNDERWATER_MIN_LORE_REQUIRED);
	bool has_shipwreck = !shipwreck_val.empty();
	vector<Coordinate> water_coords;

	if (RNG::percent_chance(PCT_CHANCE_UNDERWATER_ITEMS))
	{
		generation_rate = RNG::range(PCT_CHANCE_UNDERWATER_ITEMS_LOWER, PCT_CHANCE_UNDERWATER_ITEMS_UPPER);
	}

	if (RNG::percent_chance(PCT_CHANCE_ROCKY_BOTTOM))
	{
		rock_generation_rate = RNG::range(PCT_CHANCE_ROCK_LOWER, PCT_CHANCE_ROCK_UPPER);
	}

	if (above_water_map == nullptr)
	{
		fill(result_map, TileType::TILE_TYPE_ROCKY_EARTH);

		TilesContainer& tc = result_map->get_tiles_ref();

		for (auto& tc_pair : tc)
		{
			tc_pair.second->set_submerged(true);
		}
	}
	else
	{
		result_map->set_property(MapProperties::MAP_PROPERTIES_CANNOT_DIG, std::to_string(true));
		TilesContainer& tc = above_water_map->get_tiles_ref();
		TilePtr tile;
		Coordinate c;

		for (auto& tc_pair : tc)
		{
			if (tc_pair.second != nullptr)
			{
				TilePtr above_tile = tc_pair.second;
				TileType att = above_tile->get_tile_type();
				TileSuperType atst = above_tile->get_tile_super_type();
				bool should_generate_items = true;

				if (atst == TileSuperType::TILE_SUPER_TYPE_GROUND &&
					  att != TileType::TILE_TYPE_PIER)
				{
					tile = std::make_shared<RockTile>();
					should_generate_items = false;
				}	
				else if (att == TileType::TILE_TYPE_SEA)
				{
					tile = std::make_shared<SeabedTile>();
				}
				else if (att == TileType::TILE_TYPE_RIVER || att == TileType::TILE_TYPE_SPRINGS)
				{
					tile = std::make_shared<RockyEarthTile>();
				}
				else 
				{
					tile = std::make_shared<RockyEarthTile>();
				}

				tile->set_submerged(true);
				c = MapUtils::convert_map_key_to_coordinate(tc_pair.first);

				if (should_generate_items)
				{
					add_items(tile, att, generation_rate, rock_generation_rate);

					if (has_shipwreck)
					{
						water_coords.push_back(c);
					}
				}

				result_map->insert(c, tile);
			}
		}
	}

	if (has_shipwreck)
	{
		int shipwreck_value = String::to_int(shipwreck_val);
		create_shipwreck(result_map, water_coords, shipwreck_value);
	}

	return result_map;
}

void UnderwaterGenerator::add_items(TilePtr tile, const TileType att, const int generation_rate, const int rock_generation_rate)
{
	if (RNG::percent_chance(rock_generation_rate))
	{
		string item_id = ItemIdKeys::ITEM_ID_STONE;

		if (RNG::percent_chance(20))
		{
			item_id = ItemIdKeys::ITEM_ID_ROCK;
		}

		ItemPtr rock = ItemManager::create_item(item_id);
		tile->get_items()->merge_or_add(rock, InventoryAdditionType::INVENTORY_ADDITION_BACK);
	}

	if (att == TileType::TILE_TYPE_SHOALS)
	{
		if (RNG::percent_chance(30))
		{
			ItemPtr rock = ItemManager::create_item(ItemIdKeys::ITEM_ID_HUGE_ROCK);
			tile->get_items()->merge_or_add(rock, InventoryAdditionType::INVENTORY_ADDITION_BACK);
		}
	}
	else if (att == TileType::TILE_TYPE_SPRINGS)
	{
		if (RNG::percent_chance(PCT_CHANCE_SPRINGS_IVORY))
		{
			ItemPtr ivory = ItemManager::create_item(ItemIdKeys::ITEM_ID_CURRENCY, RNG::range(1, 6));
			tile->get_items()->merge_or_add(ivory, InventoryAdditionType::INVENTORY_ADDITION_BACK);
		}
	}
	else
	{
		if (att == TileType::TILE_TYPE_RIVER)
		{
			if (RNG::percent_chance(15))
			{
				ItemPtr clay = ItemManager::create_item(ItemIdKeys::ITEM_ID_CLAY, RNG::range(1, 2));
				tile->get_items()->merge_or_add(clay, InventoryAdditionType::INVENTORY_ADDITION_BACK);
			}
		}

		if (RNG::percent_chance(generation_rate))
		{
			pair<string, int> gen_pair = underwater_item_ids.at(RNG::range(0, underwater_item_ids.size() - 1));

			if (RNG::percent_chance(gen_pair.second))
			{
				ItemPtr item = ItemManager::create_item(gen_pair.first);
				tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
			}
		}
	}
}

void UnderwaterGenerator::create_shipwreck(MapPtr uw_map, const vector<Coordinate>& water_coords, const int shipwreck_value)
{
	if (!water_coords.empty() && shipwreck_value > 0)
	{
		vector<string> addl_items = {};
		map<string, int> addl_item_chances = { {ItemIdKeys::ITEM_ID_BOARD_WITH_NAIL_IN_IT, 6}, 
			                                     {ItemIdKeys::ITEM_ID_CLAY_POT, 7}, 
			                                     {ItemIdKeys::ITEM_ID_FISHING_ROD, 4}, 
			                                     {ItemIdKeys::ITEM_ID_INKPOT,5}, 
			                                     {ItemIdKeys::ITEM_ID_MAGICI_SHARD, 2}, 
			                                     {ItemIdKeys::ITEM_ID_PILE_OF_BONES, 5}, 
			                                     {ItemIdKeys::ITEM_ID_INTACT_SKELETON, 3}, 
			                                     {ItemIdKeys::ITEM_ID_LUMBER, 80} };
		int extra_passes = RNG::range(3, 5);

		for (int i = 0; i < extra_passes; i++)
		{
			for (const auto& ai_pair : addl_item_chances)
			{
				if (RNG::percent_chance(ai_pair.second))
				{
					addl_items.push_back(ai_pair.first);
				}
			}
		}

		Coordinate shipwreck_coord = CoordUtils::end();

		if (!water_coords.empty())
		{
			shipwreck_coord = water_coords.at(RNG::range(0, water_coords.size() - 1));
		}

		generate_shipwreck(uw_map, shipwreck_coord, addl_items, shipwreck_value);
	}
}

MapType UnderwaterGenerator::get_map_type() const
{
	return MapType::MAP_TYPE_UNDERWATER;
}
