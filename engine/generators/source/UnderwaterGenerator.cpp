#include "UnderwaterGenerator.hpp"
#include "ItemManager.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RockTile.hpp"
#include "RockyEarthTile.hpp"
#include "RNG.hpp"
#include "SeabedTile.hpp"

using namespace std;

const int UnderwaterGenerator::PCT_CHANCE_CORPSES = 5;
const int UnderwaterGenerator::PCT_CHANCE_SPRINGS_IVORY = 10;
const int UnderwaterGenerator::PCT_CHANCE_UNDERWATER_ITEMS = 20;
const int UnderwaterGenerator::PCT_CHANCE_UNDERWATER_ITEMS_LOWER = 2;
const int UnderwaterGenerator::PCT_CHANCE_UNDERWATER_ITEMS_UPPER = 8;

UnderwaterGenerator::UnderwaterGenerator(MapPtr above_map, const string& map_exit_id)
: above_water_map(above_map), Generator(map_exit_id, TileType::TILE_TYPE_SEA)
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
	bool generate_underwater_items = RNG::percent_chance(PCT_CHANCE_UNDERWATER_ITEMS);
	int generation_rate = RNG::range(PCT_CHANCE_UNDERWATER_ITEMS_LOWER, PCT_CHANCE_UNDERWATER_ITEMS_UPPER);

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

				if (generate_underwater_items && should_generate_items)
				{
					add_items(tile, att, generation_rate);
				}

				c = MapUtils::convert_map_key_to_coordinate(tc_pair.first);
				result_map->insert(c, tile);
			}
		}
	}

	return result_map;
}

void UnderwaterGenerator::add_items(TilePtr tile, const TileType att, const int generation_rate)
{
	if (att == TileType::TILE_TYPE_SPRINGS)
	{
		if (RNG::percent_chance(PCT_CHANCE_SPRINGS_IVORY))
		{
			ItemPtr ivory = ItemManager::create_item(ItemIdKeys::ITEM_ID_CURRENCY, RNG::range(1, 6));
			tile->get_items()->merge_or_add(ivory, InventoryAdditionType::INVENTORY_ADDITION_BACK);
		}
	}
	else
	{
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

MapType UnderwaterGenerator::get_map_type() const
{
	return MapType::MAP_TYPE_UNDERWATER;
}