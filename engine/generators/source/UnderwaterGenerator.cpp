#include "UnderwaterGenerator.hpp"
#include "RockyEarthTile.hpp"
#include "RockTile.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"

using namespace std;

UnderwaterGenerator::UnderwaterGenerator(MapPtr above_map, const string& map_exit_id)
: above_water_map(above_map), Generator(map_exit_id, TileType::TILE_TYPE_SEA)
{
}

MapPtr UnderwaterGenerator::generate(const Dimensions& dim)
{
	MapPtr result_map = std::make_shared<Map>(dim);
	result_map->set_permanent(true);

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
		MapExitPtr map_exit = std::make_shared<MapExit>();
		map_exit->set_map_id(above_water_map->get_map_id());
		result_map->set_map_exit(Direction::DIRECTION_UP, map_exit);
		result_map->set_property(MapProperties::MAP_PROPERTIES_CANNOT_DIG, std::to_string(true));
		TilesContainer& tc = above_water_map->get_tiles_ref();
		
		for (auto& tc_pair : tc)
		{
			if (tc_pair.second != nullptr)
			{
				TilePtr tile;
				TilePtr above_tile = tc_pair.second;
				TileType att = above_tile->get_tile_type();
				TileSuperType atst = above_tile->get_tile_super_type();

				if (atst == TileSuperType::TILE_SUPER_TYPE_GROUND &&
					  att != TileType::TILE_TYPE_PIER)
				{
					tile = std::make_shared<RockTile>();
				}
				else
				{
					// JCD FIXME variation!
					tile = std::make_shared<RockyEarthTile>();
				}

				tile->set_submerged(true);

				Coordinate c = MapUtils::convert_map_key_to_coordinate(tc_pair.first);
				result_map->insert(c, tile);
			}
		}
	}

	return result_map;
}

MapType UnderwaterGenerator::get_map_type() const
{
	return MapType::MAP_TYPE_UNDERWATER;
}