#include "SkyGenerator.hpp"
#include "MapProperties.hpp"

using namespace std;

SkyGenerator::SkyGenerator(const string& map_id)
: Generator(map_id, TileType::TILE_TYPE_AIR)
{
}

MapPtr SkyGenerator::generate(const Dimensions& dim)
{
	MapPtr result_map = std::make_shared<Map>(dim);
	result_map->set_property(MapProperties::MAP_PROPERTIES_OPEN_SKY, std::to_string(true));
	result_map->set_permanent(true);
	fill(result_map, TileType::TILE_TYPE_AIR);

	return result_map;
}

MapType SkyGenerator::get_map_type() const
{
	return MapType::MAP_TYPE_AIR;
}
